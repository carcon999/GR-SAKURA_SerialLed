/*GR-SAKURA Sketch Template Version: V1.08*/
/*
  SerialCtrlDirect.cpp

  Windows用のシリアルLEDプログラマーから演出確認が行えます。
  Windows用のツールは以下のサイトからダウンロード可能です。
  http://blogs.yahoo.co.jp/carcon999/37808488.html

  Windowsアプリ側の通信速度は57600bpsにしてください。
  ※Windowsアプリの「ツール」->「オプション」-> Baudrate(bps)に57600を指定します。

  This example code is in the public domain.
*/
#include "..\gr_example.h"

#ifdef ENABLE_SERIALCTRLDIRECT

#include <rxduino.h>
#include <SerialLedController.h> // library

// シリアルコントローラ用ライブラリのインスタンスを生成する。
// リセットとボーレート指定用のPIN番号を指定する。もし利用しない場合は－１を指定する。
SerialLedController controller(PIN_P24, PIN_P25);

void setup()
{
  // USBシリアルを利用する。
  Serial.begin(57600, SCI_USB0);

  // シリアルクラスと、通信速度（true:57600, false:19200）を指定する
  // ライブラリの初期化処理を利用しています。
  // 内部では、Serial3のクラスを利用しています。
  controller.begin(SCI_SCI0P2x, true);
}

void loop()
{
  delay(1);

  // LEDコントローラからの受信を転送
  if (Serial3.available())
  {
    Serial.write(Serial3.read());
  }

  // USBからの受信データを転送
  if (Serial.available())
  {
    Serial3.write((byte)Serial.read());
  }
}
#endif
