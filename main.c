#include <stdint.h>
#include <stdio.h>
//thanh ghi chứa  GPIOA và B
#define RCC_AHB2ENR (*((volatile unsigned long *)0x4002104C)) // Địa chỉ bật xung GPIO
//Thanh ghi chứa I2C,UART
#define RCC_APB1ENR (*((volatile unsigned long *)0X40021058)) // Địa chỉ bật xung  0X40021000
// Định nghĩa thanh ghi chứa SPI
#define RCC_APB2ENR    (*((volatile unsigned long *)0x40021060)) // Địa chỉ thanh ghi RCC APB2ENR
//Định nghĩa thanh ghi GPIOA 0x4000 4400
#define GPIOA_MODER (*((volatile unsigned long *)0x48000000)) // Địa chỉ thanh ghi cấu hình chế độ của GPIOA
#define GPIOA_OTYPER (*((volatile unsigned long *)0x48000004)) // Địa chỉ thanh ghi kiểu đầu ra của GPIOA
#define GPIOA_OSPEEDR (*((volatile unsigned long *)0x48000008)) // Địa chỉ tốc độ đầu ra của GPIOA
#define GPIOA_PUPDR (*((volatile unsigned long *)0x4800000C)) // Địa chỉ thanh ghi kéo lên/kéo xuống của GPIOA
#define GPIOA_AFRH (*((volatile unsigned long *)0x48000024)) // Địa chỉ thanh ghi cấu hình chức năng thay thế của GPIOA
#define GPIOA_AFRL (*((volatile unsigned long *)0x48000020)) // Địa chỉ thanh ghi cấu hình chức năng thay thế của GPIOA
#define GPIOA_BSRR     (*((volatile unsigned long *)0x48000018)) // Địa chỉ GPIOA_BSRR

//GPIO B
#define GPIOB_OTYPER   (*((volatile unsigned long *)0x48000404)) // base:0x4800 0400 ; offset :0x04
#define GPIOB_MODER   (*((volatile unsigned long *)0x48000400)) // base:0x4800 0400 ; offset :0x00     chân cấu hình in out
#define GPIOB_PUPDR    (*((volatile unsigned long *)0x4800040C)) // base:0x4800 0400 ; offset :0x0C    chân bật push-pull
#define GPIOB_IDR      (*((volatile unsigned long *)0x48000410)) // base:0x4800 0400 ; offset : 0x10   chân Data in
#define GPIOB_ODR      (*((volatile unsigned long *)0x48000414)) // base:0x4800 0400;  offset :0x14    out port B
#define GPIOB_BSRR  (*((volatile unsigned long *)0x48000418)) // base:0x4800 0400 ; offset :0x18
#define GPIOB_SPEED (*((volatile unsigned long *)0x48000408)) // base:0x4800 0400 ; offset :0x08
//base 0x40004400 USART2
#define USART2_CR1 (*((volatile unsigned long *)0x40004400)) //0x00 0x40004400
#define USART2_CR2 (*((volatile unsigned long *)0x40004404)) //0x04
#define USART2_CR3 (*((volatile unsigned long *)0x40004408)) //0x08
#define USART2_BRR (*((volatile unsigned long *)0x4000440C)) //0x0C
#define USART2_ISR (*((volatile unsigned long *)0x4000441C)) //0x1C
#define USART2_RDR (*((volatile unsigned long *)0x40004424)) //0x24
#define USART2_TDR (*((volatile unsigned long *)0x40004428)) //0x28
// Định nghĩa thanh ghi SPI1
#define SPI1_CR1 (*((volatile unsigned long *)0x40013000)) // SPI1 Control Register 1
#define SPI1_CR2 (*((volatile unsigned long *)0x40013004)) // SPI1 Control Register 2
#define SPI1_SR  (*((volatile unsigned long *)0x40013008)) // SPI1 Status Register
#define SPI1_DR  (*((volatile unsigned long *)0x4001300C)) // SPI1 Data Register

//I2C
#define I2C2_CR1 (*((volatile unsigned long *)0x40005800)) // Địa chỉ thanh ghi điều khiển I2C2 0x4000 7800
#define I2C2_CR2 (*((volatile unsigned long *)0x40005804)) // Địa chỉ thanh ghi điều khiển 2 của I2C2
#define I2C2_TIMINGR (*((volatile unsigned long *)0x40005810)) // Thanh ghi cấu hình tốc độ I2C
#define I2C2_ISR (*((volatile unsigned long *)0x40005818)) // Thanh ghi trạng thái I2C2 0x4000 5800
#define I2C2_TXDR (*((volatile unsigned long *)0x40005828)) // Thanh ghi dữ liệu truyền I2C2
#define I2C2_RXDR (*((volatile unsigned long *)0x40005824)) // Thanh ghi dữ liệu nhận I2C2
//BMP280
#define BMP280_ADDRESS 0x76
#define BMP280_REG_TEMP_MSB 0xFA
#define BMP280_REG_TEMP_LSB 0xFB
#define BMP280_REG_TEMP_XLSB 0xFC
#define BMP280_REG_PRESS_MSB 0xF7
#define BMP280_REG_PRESS_LSB 0xF8
#define BMP280_REG_PRESS_XLSB 0xF9
// Các tham số thô
uint16_t dig_T1;
int16_t  dig_T2;
int16_t  dig_T3;
uint16_t dig_P1;
int16_t  dig_P2;
int16_t  dig_P3;
int16_t  dig_P4;
int16_t  dig_P5;
int16_t  dig_P6;
int16_t  dig_P7;
int16_t  dig_P8;
int16_t  dig_P9;
//i2c
uint32_t raw_temp;
uint32_t raw_press;
volatile float temp ;
volatile float press ;
int32_t var1, var2, temp_fine;
uint32_t BMP280_ReadTemperature(void);
uint32_t BMP280_ReadPress(void);
uint64_t bmp280_compensate_P_int64(int32_t adc_P);
uint8_t USART2_Receive(void) ;
//spi
volatile uint16_t raw_tempmax = 0;
volatile float real_temp = 0;
void SPI_Init(void);
uint16_t readMax6675(void);
float CalTemp(uint16_t raw_tempmax);


//GPIO
void GPIOB_Init(void);

//các chân
//USART2_TX :PA2
//USART2_RX :PA3

//SPI1_cs   :PA4
//SPI1_CLK  :PA5
//SPI1_MISO :PA6

//I2C2_SDA  :PA8
//I2C2_SCL  :PA9


int main(void) {
	GPIOB_Init();
    SPI_Init();
	I2C2_Init();
	USART2_Init();
	BMP280_Init();
	read_calibration_data();
    while (1) {
    	Handle_Data_From_ESP32();
    	Max6675_ReadData();
    	BMP280_ReadData();
        delay_ms(1000);
    }
}

void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 1000; i++);
}

void USART2_Init(void) {
    // Bật xung GPIOA và USART2
    RCC_AHB2ENR |= (1 << 0); // Bật xung GPIOA
    RCC_APB1ENR |= (1 << 17); // Bật xung USART2

    // Cấu hình PA2 (TX) và PA3 (RX) cho USART2
    GPIOA_MODER &= ~((0x3 << 4) | (0x3 << 6)); // Clear PA2 and PA3
    GPIOA_MODER |= ((0x2 << 4) | (0x2 << 6));  // Set PA2 and PA3 to Alternate Function mode
    GPIOA_AFRL &= ~((0xF << 8) | (0xF << 12)); // Clear AF for PA2 and PA3
    GPIOA_AFRL |= ((0x7 << 8) | (0x7 << 12));  // Set AF7 for PA2 and PA3 (USART2)

    // Cấu hình Baud rate cho USART2 (9600) cho 16 MHZ nếu không set thì là oversampling16 cr1('15')
    USART2_BRR = 0x0683;//  0x0683= 1667(16.10^6 /9600)             0x008B (đã tính thêm nếu muốn ở 115200)

    // Cấu hình các bit điều khiển USART2 cho UART (Asynchronous mode)
    USART2_CR1 &= ~((1 << 12) | (1 << 28)); //  M[1:0] = ‘00’: 1 start bit, 8 Data bits, n Stop bit
    USART2_CR1 &= ~(1 << 10); // Clear PS bit (No parity)
    USART2_CR2 &= ~(1 << 12); // Clear STOP bits (1 stop bit)

    // Kích hoạt nhận và truyền dữ liệu qua USART2
    USART2_CR1 |= (1 << 3);   // Enable transmitter (TE)
    USART2_CR1 |= (1 << 2);   // Enable receiver (RE)
    USART2_CR1 |= (1 << 0);   // Enable USART (UE)
}
void USART2_Transmit(uint8_t data) {
    USART2_TDR = data;
    while (!(USART2_ISR & (1 << 6)));//TC
}

void USART2_Transmit_String(const char *str) {
    while (*str) {
        USART2_Transmit((uint8_t)*str); // Gửi từng ký tự
        str++;
    }
}
uint8_t USART2_Receive(void) {
    while (!(USART2_ISR & (1 << 5))); // Chờ cho đến khi RXNE (Receive Data Register Not Empty) được set
    return (uint8_t)(USART2_RDR & 0xFF); // Đọc dữ liệu nhận được từ thanh ghi RDR 8
}

void Handle_Data_From_ESP32(void) {
    uint8_t received_data = USART2_Receive(); // Nhận dữ liệu từ ESP32
    if (received_data == '1') {
    GPIOB_ODR |= (1 << 14); // Bật LED2 (PB14)
    GPIOB_ODR |= (1 << 13); // Bật LED1 (PB13)
    }
    if (received_data == '0') {
    GPIOB_ODR &= ~(1 << 14); // Tắt LED2 (PB14)
    GPIOB_ODR &= ~(1 << 13); // Tắt LED1 (PB13)
    }
}

// Hàm khởi tạo I2C2
void I2C2_Init(void) {
    RCC_AHB2ENR |= (1 << 0); // Bật xung GPIOA
    RCC_APB1ENR |= (1 << 22); // Bật xung I2C2

    // Cấu hình PA8 cho I2C2_SDA
    GPIOA_MODER &= ~(3 << 16); //xóa các bit 16 và 17
    GPIOA_MODER |= (2 << 16);  // PA8 làm alternate function
    GPIOA_AFRH |= (4 << 0); // AF4 cho I2C2 trên PA8
    GPIOA_OTYPER |= (1 << 8); // Output open-drain cho PA8
    GPIOA_OSPEEDR |= (3 << 16); // High Speed cho PA8
    GPIOA_PUPDR |= (1 << 16); // Pull-up cho PA8

    // Cấu hình PA9 cho I2C2_SCL
    GPIOA_MODER &= ~(3 << 18); //xóa các bit 18 19
    GPIOA_MODER |= (2 << 18);  // PA9 làm alternate function
    GPIOA_AFRH |= (4 << 4); // AF4 cho I2C2 trên PA9
    GPIOA_OTYPER |= (1 << 9); // Output open-drain cho PA9
    GPIOA_OSPEEDR |= (3 << 18); // High Speed cho PA9
    GPIOA_PUPDR |= (1 << 18); // Pull-up cho PA9

    I2C2_CR1 &= ~(1 << 0);  // Tắt I2C2 trước khi cấu hình
    // Cấu hình tốc độ I2C 100kHZ ở
    I2C2_TIMINGR =  (0x3 << 28)   // PRESC = 0x3 (prescaler)
                  | (0x13 << 0)   // SCLL = 0x13 (Low Period)
                  | (0xF << 8)    // SCLH = 0xF (High Period)
                  | (0x2 << 16)   // SDADEL = 0x2 (Data Hold Time)
                  | (0x4 << 20);  // SCLDEL = 0x4 (SCL to SDA Setup Time)
    I2C2_CR1 |= (1 << 0);   // Bật I2C2
    delay_ms(300);
}
void I2C_Write(uint8_t device_addr, uint8_t reg_addr, uint8_t data) {
    I2C2_CR2 &= ~(1 << 11); // 7-bit address mode
    I2C2_CR2 = (device_addr << 1) | (0 << 10) | (2 << 16); // Set device address and NBYTES = 2
    I2C2_CR2 |= (1 << 13);  // Send START condition
    while (!(I2C2_ISR & (1 << 1)));  // Wait for TXIS (empty)
    I2C2_TXDR = reg_addr;  // Send register address
    while (!(I2C2_ISR & (1 << 1)));  // Wait for TXIS
    I2C2_TXDR = data;  // Send data
    while (!(I2C2_ISR & (1 << 6)));  // Wait for TC
    I2C2_CR2 |= (1 << 14);  // Send STOP condition
}

uint32_t I2C_Read_Bytes(uint8_t device_addr, uint8_t reg_addr, uint8_t num_bytes) {
    uint32_t data = 0;
    I2C2_CR2 = (device_addr << 1) | (0 << 10) | (1 << 16);
    I2C2_CR2 |= (1 << 13); // Send START condition
    while (!(I2C2_ISR & (1 << 1)));//TXIS
    I2C2_TXDR = reg_addr; // Send register address
    while (!(I2C2_ISR & (1 << 6)));//TC
    I2C2_CR2 = (device_addr << 1) | (1 << 10) | (num_bytes << 16);
    I2C2_CR2 |= (1 << 13); // Gửi điều kiện START
    for (uint8_t i = 0; i < num_bytes; i++) {
        while (!(I2C2_ISR & (1 << 2))); // Chờ cho RXNE không rỗng
        data = (data << 8) | I2C2_RXDR;
    }
    while (!(I2C2_ISR & (1 << 6)));//TC
    I2C2_CR2 |= (1 << 14); // Gửi STOP condition
    return data;
}

void read_calibration_data(void) {
    dig_T1 = (uint16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x88, 2);
    dig_T2 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x8A, 2);
    dig_T3 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x8C, 2);
    dig_P1 = (uint16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x8E, 2);
    dig_P2 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x90, 2);
    dig_P3 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x92, 2);
    dig_P4 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x94, 2);
    dig_P5 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x96, 2);
    dig_P6 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x98, 2);
    dig_P7 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x9A, 2);
    dig_P8 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x9C, 2);
    dig_P9 = (int16_t)I2C_Read_Bytes(BMP280_ADDRESS, 0x9E, 2);
}

int32_t BMP280_CalculateTemperature(int32_t raw_temp) {
    var1 = ((((raw_temp >> 3) - ((int32_t)dig_T1 << 1))) * (int32_t)dig_T2) >> 11;
    var2 = (((((raw_temp >> 4) - (int32_t)dig_T1) * ((raw_temp >> 4) - (int32_t)dig_T1)) >> 12) * (int32_t)dig_T3) >> 14;
    temp_fine = var1 + var2;
    return (temp_fine * 5 + 128) >> 8;
}

uint32_t BMP280_ReadTemperature(void) {
    uint8_t temp_msb, temp_lsb, temp_xlsb;
    uint32_t raw_temp;
    temp_msb = I2C_Read_Bytes(BMP280_ADDRESS, BMP280_REG_TEMP_MSB, 1);
    temp_lsb = I2C_Read_Bytes(BMP280_ADDRESS, BMP280_REG_TEMP_LSB, 1);
    temp_xlsb =I2C_Read_Bytes(BMP280_ADDRESS, BMP280_REG_TEMP_XLSB, 1);

    raw_temp = (temp_msb << 12) | (temp_lsb << 4) | (temp_xlsb >> 4);
    return raw_temp ;
}

uint32_t BMP280_ReadPress(void) {
    uint8_t press_msb, press_lsb, press_xlsb;
    uint32_t raw_press;
    press_msb = I2C_Read_Bytes(BMP280_ADDRESS, BMP280_REG_PRESS_MSB, 1);
    press_lsb = I2C_Read_Bytes(BMP280_ADDRESS, BMP280_REG_PRESS_LSB, 1);
    press_xlsb =I2C_Read_Bytes(BMP280_ADDRESS, BMP280_REG_PRESS_XLSB, 1);

    raw_press = (press_msb << 12) | (press_lsb << 4) | (press_xlsb >> 4);
    return raw_press ;
}
uint64_t bmp280_compensate_P_int64(int32_t adc_P) {
    int64_t var1, var2, p;
    var1 = ((int64_t)temp_fine) - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = (((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4));

    return (uint32_t)p/184;
}
void BMP280_ReadData(void) {
	  char buffer[50];
    raw_temp = BMP280_ReadTemperature();  // Đọc nhiệt độ raw
    temp = (BMP280_CalculateTemperature(raw_temp)/260.0);// tính toán ra số thực
    raw_press = BMP280_ReadPress();
    press = bmp280_compensate_P_int64(raw_press)/1250.0;
    sprintf(buffer, "T %.2f\n", temp);
    USART2_Transmit_String(buffer); // Gửi chuỗi nhiệt độ
    sprintf(buffer, "P %.2f\n", press);
    USART2_Transmit_String(buffer); // Gửi chuỗi nhiệt độ
//        	 if (press >= 110 || press <= 90) { // Nếu dữ liệu nhận được là '1'
//        	        GPIOB_ODR |= (1 << 14); // Bật LED2 (PB14)
//        	        GPIOB_ODR |= (1 << 13); // Bật LED1 (PB13)
//        	 }
//        	if (temp >= 30 || temp <= 20)  {
//        	        GPIOB_ODR &= ~(1 << 14); // Tắt LED2 (PB14)
//        	        GPIOB_ODR &= ~(1 << 13); // Tắt LED1 (PB13)
//        	 }

}
void BMP280_Init(void) {
	I2C_Write(BMP280_ADDRESS, 0xF4, 0x27);//0xF4 là thanh ctrl_meas còn ox27 là 001 001 11(normal)
    delay_ms(3000);
}

void SPI_Init(void) {
	//gpio Pa4,pa5,pa6
    RCC_AHB2ENR |= (1 << 0); // Bật xung clock cho GPIOA
    // Cấu hình PA4 (CS), PA5 (SCK), PA6 (MISO)
    GPIOA_MODER &= ~((3 << (4 * 2)) | (3 << (5 * 2)) | (3 << (6 * 2))); // Xóa mode của PA4, PA5, PA6
    GPIOA_MODER |= (1 << (4 * 2)) | (2 << (5 * 2)) | (2 << (6 * 2));    // PA4: Output, PA5 & PA6: Alternate Function
    GPIOA_AFRL &= ~((0xF << (5 * 4)) | (0xF << (6 * 4))); // Xóa AF của PA5, PA6
    GPIOA_AFRL |= (5 << (5 * 4)) | (5 << (6 * 4));        // AF5 cho SPI1 (PA5, PA6)
    GPIOA_OSPEEDR |= (3 << (5 * 2)) | (3 << (6 * 2)); // High Speed cho PA5, PA6
    GPIOA_OTYPER &= ~(1 << 4);                       // Push-Pull cho PA4
    //spi
    RCC_APB2ENR |= (1 << 12); // Bật clock cho SPI1
    SPI1_CR1 = 0;             // Reset các thiết lập SPI1_CR1
    SPI1_CR1 |= (1 << 2);     // Chọn chế độ Master
    SPI1_CR1 |= ((1 << 9) | (1 << 8)); // Kích hoạt SSM và SSI
    SPI1_CR1 &= ~((1 << 1) | (1 << 0)); // CPOL = 0, CPHA = 0
    SPI1_CR1 |= (4 << 3);     // Tốc độ Baudrate = fPCLK/16
    SPI1_CR2 = 0;             // Reset các thiết lập SPI1_CR2
    SPI1_CR2 |= (0xF << 8);   // Data size: 16-bit
    SPI1_CR1 |= (1 << 6);     // Bật SPI1
}

uint16_t readMax6675(void) {
    uint16_t data = 0;
    GPIOA_BSRR = (1 << 20); // CS (PA4) xuống LOW
    delay_ms(1000);
    data = SPI1_DR;
    SPI1_DR = 0x00; // Gửi lệnh đọc
    while (!(SPI1_SR & (1 << 0))); // Đợi RXNE (Dữ liệu đã sẵn sàng)
    data = SPI1_DR;  // Nhận dữ liệu
    GPIOA_BSRR = (1 << 4); // CS (PA4) lên HIGH
    delay_ms(1000);
    return (data >> 3); // Loại bỏ 3 bit thấp
}

float CalTemp(uint16_t raw_tempmax) {
    return (raw_tempmax * 0.25); // MAX6675 cung cấp giá trị nhiệt độ với độ phân giải 0.25°C

}
void Max6675_ReadData(void) {
char buffer[50];
raw_tempmax = readMax6675();       // Đọc dữ liệu nhiệt độ từ MAX6675
real_temp = CalTemp(raw_tempmax); // Chuyển đổi dữ liệu thô thành nhiệt độ thực
sprintf(buffer, "M %.2f\n", real_temp);
//if (real_temp >= 30 || real_temp <= 20) { // Nếu dữ liệu nhận được là '1'
////        	        GPIOB_ODR |= (1 << 15); // Bật LED3 (PB15)
//       GPIOB_ODR |= (1 << 14); // Bật LED2 (PB14)
//       GPIOB_ODR |= (1 << 13); // Bật LED1 (PB13)
//}
//else { // Nếu dữ liệu nhận được là '0'
////        	        GPIOB_ODR &= ~(1 << 15); // Tắt LED3 (PB15)
//       GPIOB_ODR &= ~(1 << 14); // Tắt LED2 (PB14)
//       GPIOB_ODR &= ~(1 << 13); // Tắt LED1 (PB13)
//}
USART2_Transmit_String(buffer); // Gửi chuỗi nhiệt độ max
}



void GPIOB_Init(void) {

	  RCC_AHB2ENR |= (1 << 1); // Bật nguồn cho port B

	    // Cấu hình các chân LED (PB13, PB14, PB15)để OUTPUT
	    GPIOB_MODER &= ~((1 << 27) | (1 << 29) | (1 << 31)); // Xóa các bit cho PB13, PB14, PB15 cho trở về mức 0
	    GPIOB_MODER |= (1 << 26) | (1 << 28) | (1 << 30);    // Đặt các bit trở về mức 1, theo cặp bit [31:30] =P15 .... 0:1 là output

	    // Cấu hình các chân button (PB11, PB12) để INPUT
	    GPIOB_MODER &= ~((1 << 24) | (1 << 25) | (1 << 22) | (1 << 23)); // xóa các bit để cho về mức 0 [25:24][0:0] là input P12 ....

	    // Pull-down cho các nút nhấn
	    GPIOB_PUPDR |= (1 << 25) | (1 << 23); // Đặt bit 25, 23 =1
	    GPIOB_PUPDR &= ~((1 << 24) | (1 << 22)); // Xóa các bit để về 0 [25:24] [1:0] là pull down

	    //     Push-pull cho các chân LED
	    //    GPIOB_OTYPER &= ~(1 << 15); // Push-pull cho pin 15
	    //    GPIOB_OTYPER &= ~(1 << 14); // Push-pull cho pin 14
	    //    GPIOB_OTYPER &= ~(1 << 13); // Push-pull cho pin 13
}



//    USART2_CR1 &= ~(1 << 15);//Oversampling by 16
//    | (1 << 28)
//void USART2_Transmit(uint8_t data) {
//    // Chờ đến khi TDR (Transmit Data Register) trống
////    while (!(USART2_ISR & (1 << 7)));  // Khi bit TXFNF = 1: TXFIFO không đầy, có thể ghi dữ liệu mới.
//    // Gửi dữ liệu
//    USART2_TDR = data;
//    while (!(USART2_ISR & (1 << 6)));//TC
//}

