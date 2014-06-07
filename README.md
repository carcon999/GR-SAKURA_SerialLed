GR-SAKURA_SerialLed
===================

[フルカラーLEDコントローラ用シールド](http://blogs.yahoo.co.jp/carcon999/folder/1250867.html)
を[GR-SAKURA](http://sakuraboard.net/gr-sakura.html)で簡単に利用するためのライブラリ＆サンプルです。  本ライブラリを利用することで、シリアルコマンドのテーブルを指定するだけで、LEDの演出を切り替えることができるようになります。  
![Image](https://raw.githubusercontent.com/carcon999/GR-SAKURA_SerialLed/master/img/IMG_5213.jpg)

# 利用方法

 1. Releaseされた[GrSerialLedShield.zip](https://github.com/carcon999/GR-SAKURA_SerialLed/releases)をダウンロードします。（ファイル名やフォルダ名は変更しないでください。）
 2. [Webコンパイラ](http://update.renesas.com/gur/compiler.do?&languageCode=jp)を起動し、任意のプロジェクトを生成します。（名前はご自由に）
 3. 生成する際のスケルトンは、GR-SAKURA_Sketch_V1.08.zipを選択しします。
 4. プロジェクトのツリーを右クリックし、「zipダウンロード」を選択します。
 5. ビルドボタンを押下し、オブジェクトが生成されれば完了です。

# 実行方法

 JP1の設定を変更します。
 JP1の上段・下段を共に1-2ショートとします。GR-SAKURAのPIN_P20, PIN_P21のシリアルポートを利用する設定とします。(写真を参考にしてください)
 つぎに生成されたオブジェクトを本体に書き込みます。

# 使い方

 gr_sketch.cppの中にled_play_listのテーブルが存在します。
 このテーブルを修正することで簡単に別なLED演出に変更することができます。
 
 テーブルに記述するコマンドについては、[ここ](https://dl.dropboxusercontent.com/u/71549646/external/LedUartCommands.pdf)にドキュメントがあります。
 
 しかし、コマンドを人手で作り出すのは少し大変な作業です。そこで、[Windows用の生成ソフト](http://blogs.yahoo.co.jp/carcon999/37808488.html)が用意されています。これを利用することで、簡単にコマンドを作成することや、シミュレーションすることが可能になりますので合わせて活用してください。
 
 また、本ファイルにはいくつかのサンプルがふくまれています。
 gr_example.hファイル内に、サンプルを切り替えるマクロが用意されていますので、切り替えて試してください。

## その他

その他の利用方法については、examplesが参考になります。

# Functions

## コンストラクタ

- SerialLedController(const int _pinreset, const int _pinbr)
 + `const int _pinreset` :
    リセット制御端子を指定する。制御端子を利用しない場合は、-1を指定する。
    省略した場合は、PIN_P23
 + `const int _pinbr` :
    通信速度制御端子を指定する。制御端子を利用しない場合は、-1を指定する。
    省略した場合は、PIN_P24

## begin

利用開始指示。利用開始前に必ず指定する。  
利用するシリアルの種別とその通信レート（57600bps/19200bps）を指定する必要があります。

- void begin(SCI_PORT port, const boolean _hispeed = true)
 + `SCI_PORT port` :
    種別を指定する。(SCI_SCI2A,SCI_SCI2B,SCI_SCI6B,SCI_SCI0P2x)
    ※CSI_SCI0P2xを利用することを期待しています。
 + `const boolean _hispeed` :
    シリアル通信速度の高低を指定する。省略時:true。true:57600bps, false:19200bps

## write

LEDコントローラに制御コマンドを送る。制御コマンドには、LEDの演出だけでなく各種制御コマンドも含まれる。

- boolean write(const uint8_t tbl[][SERIALCOMMAND_FIXEDLEN], int size)
 + `const uint8_t tbl[][SERIALCOMMAND_FIXEDLEN]` :
    制御コマンドのテーブルを指定する。（8byte境界であること）
 + `int size` :
    指定したテーブルのサイズ

## start

演出開始用のコマンドを送る。
{0x94, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} を送信します。

- void start(void)
 + `void` :
    なし

## stop

演出停止用のコマンドを送る。
{0x94, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} を送信します。

- void stop(void)
 + `void` :
    なし

## reset

LEDコントローラのリセット端子を操作しリセットする。
コンストラクタでリセット制御端子が指定されている場合のみ有効です。
また、通信速度制御端子が指定されていれば、合わせて通信速度の指定（HI/LOW）を行います。

- void reset(void)
 + `void` :
    なし
