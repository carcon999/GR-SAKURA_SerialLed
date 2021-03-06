/*GR-SAKURA Sketch Template Version: V1.08*/
/*
  Sw1Bar.cpp

  Bar演出を確認します。
  ※SW1を押下する毎に演出が切り替わります。（パラメータ違い４種類）

  This example code is in the public domain.
*/
#include "..\gr_example.h"

#ifdef ENABLE_SW1BAR

#include <rxduino.h>
#include <SerialLedController.h> // library

/* Commands Table. Run sequentially. */
const uint8_t led_play_list1[][SERIALCOMMAND_FIXEDLEN] =
{
  { 0x94, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec Start. */
  { 0x90, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 }, /* System */
  { 0x96, 0x1E, 0x00, 0x00, 0x06, 0x32, 0x14, 0x03 }, /* Bar color:red right 50ms */
  { 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec End. */
};

const uint8_t led_play_list2[][SERIALCOMMAND_FIXEDLEN] =
{
  { 0x94, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec Start. */
  { 0x90, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 }, /* System */
  { 0x96, 0x1E, 0x00, 0x00, 0x07, 0x32, 0x14, 0x03 }, /* Bar color:red left 50ms */
  { 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec End. */
};

const uint8_t led_play_list3[][SERIALCOMMAND_FIXEDLEN] =
{
  { 0x94, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec Start. */
  { 0x90, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 }, /* System */
  { 0x96, 0x1E, 0x00, 0x00, 0x06, 0x19, 0x64, 0x03 }, /* Bar color:red right 25ms wait 1000ms */
  { 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec End. */
};

const uint8_t led_play_list4[][SERIALCOMMAND_FIXEDLEN] =
{
  { 0x94, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec Start. */
  { 0x90, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 }, /* System */
  { 0x96, 0x00, 0x00, 0x1E, 0x07, 0x19, 0x64, 0x03 }, /* Bar color:blue left 25ms wait 1000ms */
  { 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec End. */
};

const uint8_t (*led_play_list_array[])[SERIALCOMMAND_FIXEDLEN] = 
{
  led_play_list1, led_play_list2, led_play_list3, led_play_list4
};

const uint8_t led_play_list_size[]= 
{
  sizeof(led_play_list1), sizeof(led_play_list2), sizeof(led_play_list3), sizeof(led_play_list4)
};

// SW1が利用するPIN番号
#define PIN_SW1   (8)

// チャタリング除去用
int swVal = 0;
int swCount = 0;
// 再生位置
static int play_index = 0;

// シリアルコントローラ用ライブラリのインスタンスを生成する。
// リセットとボーレート指定用のPIN番号を指定する。もし利用しない場合は－１を指定する。
SerialLedController controller(PIN_P24, PIN_P25);

void setup()
{
  // SW1(OPTION)入力プルアップ
  pinMode(PIN_SW1, INPUT_PULLUP);

  // シリアルクラスと、通信速度（true:57600, false:19200）を指定する
  controller.begin(SCI_SCI0P2x, true);

//  // 演出用のテーブルを与える。（コントローラにデータを転送する）  
//  if(controller.write(led_play_list, sizeof(led_play_list))){
//    // 転送に成功したら演出を開始する。
//    controller.start();
//  }
}

void loop()
{
  // チャタリング除去
  swVal = digitalRead(PIN_SW1);
  if (swVal == LOW) {
    swCount += 1;
  } else {
    swCount = 0;
  }
 
  if (swCount == 10) {
    // 再生停止
    controller.stop();
    // コマンドの転送
    controller.write(led_play_list_array[play_index], led_play_list_size[play_index]);
    // 再生開始
    controller.start();

    // 0 - 3
    play_index++;
    play_index &= 0x03;
  }
 
  delay(1);
}
#endif
