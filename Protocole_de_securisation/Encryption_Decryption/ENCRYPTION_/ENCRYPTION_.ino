#include <aes.h>
#include <aes128_dec.h>
#include <aes128_enc.h>

#include <AESLib.h>


void aes128_enc_single(const uint8_t* key, void* data);
void aes128_dec_single(const uint8_t* key, void* data);
uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
char data[] = "0130293485494302"; // 16 chars == 16 bytes (octets)

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
aes128_enc_single(key, data);
Serial.print("Chiffré [encrypted] :   ");
Serial.println(data);

aes128_dec_single(key, data);
Serial.print("Déchiffré [decrypted]:   ");
Serial.println(data);
delay(2000);
Serial.println("");
}
