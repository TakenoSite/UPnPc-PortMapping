# UPNP PROTOCOL

UPnPプロトコルを、使用して、ポートマッピングを提供します。

使用にあたり、UPnPプロトコルを、実装したルーターと、ルーター設定よりUPNPを有効にする必要があります。

対応する操作の一覧

- AddPortMapping

- DeletePortMapping 

- GetPortMapping

- GetExternalIPAddress


#  How to Build

    make

# Command

ビルド後、upnpc 実行ファイルが作成されます。

実行には、各種オプションを指定し引数を設定します。



### GetExternalIPAddress  :

    upnpc -l  

### AddPortMapping:

    upnpc -a  {EXTRAN PORT} {INTERNAL PORT} {INTERNAL_CLIENT} {PROTOCOL} {LEASE DURATION} {DESCRIPTION}

### DeletePortMapping:

    upnpc -d {EXTRANL PORT} {PROTOCOL}

### GetPortMapping:

    upnpc -g

### help: 

    upnpc -h



# Document


    rfc6970


