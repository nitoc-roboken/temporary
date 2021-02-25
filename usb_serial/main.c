#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>

#define SERIAL_PORT "/dev/ttyACM0"

void delay_us(useconds_t us)
{
    usleep(us);
}

void delay_ms(useconds_t ms)
{
    usleep(ms * 1000);
}

void delay_sec(float sec)
{
    usleep((useconds_t)(sec * 1000000));
}

int main(int argc, char *argv[])
{
    unsigned char msg[] = "serial port open...\n";
    int fd;                             // ファイルディスクリプタ
    struct termios tio;                 // シリアル通信設定
    int baudRate = B115200;

    fd = open(SERIAL_PORT, O_RDWR);     // デバイスをオープンする
    if (fd < 0) {
        printf("open error %d\n", fd);
        return -1;
    }

    tio.c_cflag += CREAD;               // 受信有効
    tio.c_cflag += CLOCAL;              // ローカルライン（モデム制御なし）
    tio.c_cflag += CS8;                 // データビット:8bit
    tio.c_cflag += 0;                   // ストップビット:1bit
    tio.c_cflag += 0;                   // パリティ:None

    cfsetispeed( &tio, baudRate );
    cfsetospeed( &tio, baudRate );

    cfmakeraw(&tio);                    // RAWモード

    tcsetattr( fd, TCSANOW, &tio );     // デバイスに設定を行う

    ioctl(fd, TCSETS, &tio);            // ポートの設定を有効にする

    // 送受信処理ループ
    while(1) 
    {
        // エコーバック
        uint8_t send_buff[10];
        send_buff[0] = 0xAA;
        send_buff[1] = 0x01;  //id
        send_buff[2] = 0xdf;  //id
        send_buff[3] = 0x04;  //reg
        send_buff[4] = 0x04;  //data_len
        send_buff[5] = 0x05;  //data1
        send_buff[6] = 0x08;  //data2
        send_buff[7] = 0x05;  //data3
        send_buff[8] = 0x08;  //data4
        send_buff[9] = 0;
        for(size_t i = 1; i <= 8; i++)
        {
            send_buff[9] += send_buff[i];
        }

        write(fd, send_buff, 10);

        uint8_t read_buff[10];
        size_t read_len = read(fd, read_buff, 10);
        if(read_len == 10)
        {
            if(read_buff[0] == 0xAA)
            {
                uint8_t checksum = 0;
                for(size_t i = 1; i <= 8; i++)
                {
                    checksum += read_buff[i];
                }

                if(checksum == read_buff[9])
                {
                    printf("ID : %x, REG : %x, (%d)[%x, %x, %x, %x]\n", 
                        *((uint16_t*)&read_buff[1]),
                        *((uint8_t*)&read_buff[3]),
                        *((uint8_t*)&read_buff[4]),
                        read_buff[5],
                        read_buff[6],
                        read_buff[7],
                        read_buff[8]);
                }
            }
        }

        delay_ms(1000);      
    }

    close(fd);                              // デバイスのクローズ
    return 0;
}
