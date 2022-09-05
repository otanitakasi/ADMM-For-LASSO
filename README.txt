-----------------
 プロジェクト構造
-----------------
・admmForLasso.c     // ADMM for lasso のC言語実装プログラム
・common.c           // 共通利用関数を定義
・test.c             // 検証用実行プログラム
・boston.txt         // 検証用学習データ：scikit-learn　boston_housingを使用
・admm_model.ipynb   // 検証用Pythonモデル(jupyter実行ファイル) ; scikit-learn linear_model.lassoを使用

-----------------
 プログラム実行方法
-----------------
1. "gcc admmForLasso.c common.c test.c -o admm" によりコンパイルを行い、実行ファイル生成
2. "./admm"　を実行し、推定パラメータを出力
3. admm_model.ipynbをjupyterで実行し、scikit-learnライブラリによる推定パラメータを出力
4. C言語モデルとPythonモデルの推定パラメータを目視により比較
