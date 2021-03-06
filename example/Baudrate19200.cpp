/*GR-SAKURA Sketch Template Version: V1.08*/
/*
  Baudrate19200.cpp

  19200bpsでSerialLEDコントローラと通信します。

  This example code is in the public domain.
*/
#include "..\gr_example.h"

#ifdef ENABLE_BAUDRATE19200

#include <rxduino.h>
#include <SerialLedController.h> // library

/* Commands Table. Run sequentially. */
const uint8_t led_play_list[][SERIALCOMMAND_FIXEDLEN] =
{
  { 0x94, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec Start. */
  { 0x90, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00 }, /* system */
  { 0x95, 0x1E, 0x01, 0x0A, 0xFF, 0x00, 0x00, 0x00 }, /* rainbow */
  { 0x97, 0x20, 0x03, 0x14, 0x02, 0x00, 0x00, 0x00 }, /* seesaw */
  { 0x92, 0x00, 0x00, 0x00, 0x20, 0x00, 0x64, 0x00 }, /* shift */
  { 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec End. */
};

// シリアルコントローラ用ライブラリのインスタンスを生成する。
// リセットとボーレート指定用のPIN番号を指定する。もし利用しない場合は－１を指定する。
SerialLedController controller(PIN_P24, PIN_P25);

void setup()
{
  // シリアルクラスと、通信速度（true:57600, false:19200）を指定する
  controller.begin(SCI_SCI0P2x, false);

  // 演出用のテーブルを与える。（コントローラにデータを転送する）  
  if(controller.write(led_play_list, sizeof(led_play_list))){
    // 転送に成功したら演出を開始する。
    controller.start();
  }
}

void loop()
{
}
#endif
