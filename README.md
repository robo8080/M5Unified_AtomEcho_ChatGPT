# M5Unified_AtomEcho_ChatGPT
AIｽﾀｯｸﾁｬﾝ2の基本機能をAtomEchoに移植しました。

特徴<br>

* ATOM Echo単体で動作します。
* 音声合成にWeb版 VOICEVOXを使います。
* 音声認識に"Google Cloud STT"か"OpenAI Whisper"のどちらかを選択できます。
<br>

Google Cloud STTは、”MhageGH”さんの [esp32_CloudSpeech](https://github.com/MhageGH/esp32_CloudSpeech/ "Title") を参考にさせて頂きました。ありがとうございました。<br>
"OpenAI Whisper"が使えるようにするにあたって、多大なご助言を頂いた”イナバ”さん、”kobatan”さんに感謝致します。<br>

---

### プログラムをビルドするのに必要な物 ###
* [ATOM Echo](https://www.switch-science.com/products/6347 "Title")<br>
* VSCode<br>
* PlatformIO<br>

使用しているライブラリ等は"platformio.ini"を参照してください。<br>

---

### ChatGPTのAPIキーの取得 ###

ChatGPTのAPIキー取得方法は以下の通りです。(詳細はこのページ一番下のリンクを参照してください。)

* [OpenAIのウェブサイト](https://openai.com/ "Title")にアクセスして、アカウントを作成します。メールアドレスと携帯電話番号が必要です。
* アカウント作成後、APIキーを発行します。APIキーは有料ですが、無料期間やクレジットがあります。<br>

### Web版 VOICEVOX のAPIキーの取得 ###

* Web版 VOICEVOX のAPIキーの取得方法は、このページ（[ttsQuestV3Voicevox](https://github.com/ts-klassen/ttsQuestV3Voicevox/ "Title")）の一番下の方を参照してください。)<br>
VOICEVOXのAPIキー取得後忘れずに“VOICEVOX用API利用登録”をしてください。そうしないと音声合成が高速にならないので音声が途切れ途切れになります。

### Google Cloud Speech to Text のAPIキーの取得（音声認識にWhisperを使うときは不要） ###

Google Cloud Speech to TextのAPIキー取得方法は以下の通りです。(詳細はこのページ一番下のリンクを参照してください。)

* [Google Cloud Platformのウェブサイト](https://cloud.google.com/?hl=ja/ "Title")にアクセスして、アカウントを作成します。メールアドレスと携帯電話番号が必要です。カードの登録が必須ですが、無料トライアルや無料枠があります。
* アカウント作成後、APIキーを取得します。<br>
APIキーでSpeech to Textを有効にするのを忘れないで下さい。<br>

---

### Wi-Fiの設定 ###
* main.cppの23行目付近、SSIDとPASSWORDを設定してください。

### APIキーの設定 ###

* main.cppの43行目付近、以下を設定します。<br>
OPENAI_APIKEY<br>
VOICEVOX_APIKEY<br>
STT_APIKEY<br>

* 【注意】<br>
STT_APIKEYには"Google Cloud STTのAPIキー" または、OPENAI_APIKEYと同じものを設定します。<br>
STT_APIKEYにOPENAI_APIKEYと同じものを設定した場合は音声認識にOpenAI Whisperが使われます。

---

### 使い方 ###
* ATOM Echoの電源を入れるとLEDが緑色に点灯してWi-Fiの接続を開始し、接続が完了すると消灯します。<br>
* ボタンAを押すと、マイクからの録音が始まり音声認識で会話できるようになります。<br>
録音時間は2秒程度です。<br>

---

### ChatGPTのAPIキー取得の参考リンク ###

* [ChatGPT API利用方法の簡単解説](https://qiita.com/mikito/items/b69f38c54b362c20e9e6/ "Title")<br>

### Web版 VOICEVOX のAPIキーの取得 ###

* Web版 VOICEVOX のAPIキーの取得方法は、このページ（[ttsQuestV3Voicevox](https://github.com/ts-klassen/ttsQuestV3Voicevox/ "Title")）の一番下の方を参照してください。)<br>
VOICEVOXのAPIキー取得後忘れずに“VOICEVOX用API利用登録”をしてください。そうしないと音声合成が高速にならないので音声が途切れ途切れになります。

### Google Cloud Speech to TextのAPIキー取得の参考リンク ###

* [Speech-to-Text APIキーの取得／登録方法について](https://nicecamera.kidsplates.jp/help/feature/transcription/apikey/ "Title")<br>
<br><br><br>
