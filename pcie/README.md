# pcie

+ [layers](#lauers)

## layers

+ Transaction (транзакционный)
+ Data Link (передача данных)
+ Physical (физический)

    TLP (Transaction Layer Packet) - пакет транзакционного уровня.
    DLLP (Data Link Layer Packet) - пакет уровня передачи данных.
    PLP (Physical Layer Packet) - пакет физического уровня.

 Ядро или программный уровень (Device Core/Software Layer) устройства на передающей стороне сообщает транзакционному уровню информацию для TLP: тип транзакции, адрес абонента, количество данных, класс трафика, индекс сообщения и сами данные.




