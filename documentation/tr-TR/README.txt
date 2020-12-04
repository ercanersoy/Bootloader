Ercan Ersoy'un Önyükleyicisi 0.2

  Bütün hakları Ercan Ersoy'a aittir. Bu yazılım, GNU LGPL v3 ile
  lisanslanmıştır.

  Ercan Ersoy'un önyükleyicisi, mikrodenetleyiciler için geliştirilmektedir.
  Program yükleme HTTP üzerinden gerçekleştirilmektedir. Şu anda, yalnızca
  AVR mimairisnde ATmega328 ve eşdeğer mikrodenetleyiciler için
  geliştirilmektedir.

Yapılandırmalar:

  Ercan Ersoy'un önyükleyicisi configurations.h dosyasıyla yapılandırılır.
  Yapılandırmalar aşağıda verilmştir:

  - STRINGS_LANGUAGE -> Sözcelerin dili
  - UART_ENABLE -> UART sürücüsünün etkinliğini ayarlar
  - UART_BAUD_RATE -> UART Baud oranını ayarlar
  - ETHERNET_ADAPTER_ENABLE -> Ethernet bağdaştırıcı sürücüsünün etkinliğini
    ayarlar
  - ETHERNET_ADAPTER -> Ethernet türü
  - ETHERNET_ADAPTER_PORT_MODE_ADDRESS -> Ethernet bağdaştırıcısı tümdevre
    seçimi portunun kipinin adresi
  - ETHERNET_ADAPTER_PORT_ADDRESS -> Ethernet bağdaştırıcısı tümdevre
    seçimi portunun adresi
  - ETHERNET_ADAPTER_CHIP_SELECTION -> Ethernet bağdaştırıcısı tümdevre seçimi
    pini
  - SWITCH_PORT -> Anahtarın portunun adresi
  - SWTICH_PIN -> Anahtarın pini
  - USER_INTERFACE_TYPE -> Kullanıcı arayüzü türü
  - USER_INTERFACE_PORT -> Kullanıcı arayüzü bağlantı portu
  - HARDWARE_MAC_ADDRESS_1, HARDWARE_MAC_ADDRESS_2, HARDWARE_MAC_ADDRESS_3,
    HARDWARE_MAC_ADDRESS_4, HARDWARE_MAC_ADDRESS_5, HARDWARE_MAC_ADDRESS_6 ->
    Ağ bağdaştırıcısının MAC adresi
  - SOURCE_IP_ADDRESS_1, SOURCE_IP_ADDRESS_2, SOURCE_IP_ADDRESS_3,
    SOURCE_IP_ADDRESS_4 -> Ağ bağdaştırıcısının IP adresi
  - SUBNET_MASK_1, SUBNET_MASK_2, SUBNET_MASK_3, SUBNET_MASK_4 -> Ağ
    bağdaştırıcısının alt ağ maskesi
  - GATEWAY_IP_ADDRESS_1, GATEWAY_IP_ADDRESS_2, GATEWAY_IP_ADDRESS_3,
    GATEWAY_IP_ADDRESS_4 -> Ağ bağdaştırıcısının ağ geçidi IP adresi

Derleme ve Kurulum:

  Derleme seçenekleri, bağlama seçenekleri ve program belleğine yazma
  seçenekleri Makefile'dedir. Kullanılabilir Makefile seçenekleri aşağıda
  verilmiştir:

  - all -> Ercan Ersoy'un önyükleyicisini derler
  - install -> Ercan Ersoy'un önyükleyicisini mikrodenetleyiciye yükler
  - set-fuses -> Mikrodenetleyicinin fuse bitlerini ayarlar
  - clean -> İkili dosyaları ve nesne dosyalarını siler
  - clean-objects -> Yalnızca, nesne dosyalarını siler

  Varsayılan yükleyici USBtinyISP'dir.

Kullanım:

  HTTP kullanıcı arayüzünü tarayıcıda görüntülemek için anahtar pinine
  mantıksal bir veriniz ve sonra ağ tarayıcısı yoluyla istek gönderiniz.

  Mantıksal bir vermek için anahtar kullanabilirsiniz.

  Ağ bağdaştırıcısının varsayılan IP adresi 192.168.0.5'tir.
  Ağ bağdaştırıcısının varsayılan salt ağ maskesi 255.255.255.0'dır.
  Ağ bağdaştırıcısının varsayılan IP adresi 192.168.0.1'dir.

  Ercan Ersoy'un önyükleyicisi, Mozilla Firefox'ta denenmiştir.

Sürüm Geçmişi:

  * 0.2 (04.12.2020): .gitignore dosyası ve README.md dosyaları eklendi.
                      Lisans, MIT Lisansı olarak değiştirildi.
                      README.txt dosyaları güncellendi.

  * 0.1 (08.08.2019): İlk sürüm
