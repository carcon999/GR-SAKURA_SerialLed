/*GR-SAKURA Sketch Template Version: V1.08*/

// ★サンプルを切り替えるためには、下記のヘッダーファイルを参照してください。
#include "gr_example.h"

#ifdef ENABLE_MAIN

#include <rxduino.h>
#include <SerialLedController.h> // library

/* Commands Table. Run sequentially. */
const uint8_t led_play_list[][SERIALCOMMAND_FIXEDLEN] =
{
  { 0x94, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec Start. */
  { 0x90, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 }, /* system */
  { 0x95, 0x36, 0x01, 0x05, 0xF4, 0x01, 0x00, 0x00 }, /* Rainbow  mode:Individual 5ms */
  { 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec End. */
};

// シリアルコントローラ用ライブラリのインスタンスを生成する。
// リセットとボーレート指定用のPIN番号を指定する。もし利用しない場合は－１を指定する。
SerialLedController controller(PIN_P24, PIN_P25);

void setup()
{
  // シリアルクラスと、通信速度（true:57600, false:19200）を指定する
  controller.begin(SCI_SCI0P2x, true);

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
