#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>


//funcao sonda
//chamada na insercao do dispositivo se e somente se nenhum outro driver nos precedeu
static int pen_probe (struct usb_interface *interface , const struct usb_device_id *id){
	printk(KERN_INFO "[*] Pen Drive (%04X:%04X) Plugged\n" , id->idVendor , id->idProduct);
	return 0;
}

//disconecta
static void pen_disconnect(struct usb_interface *interface){
	printk(KERN_SOH "[*] Pen drive removido\n");
}

//usb_device_id
static struct usb_device_id pen_table[] = {
	//1221:3234 idVendor e idProduct
	{USB_DEVICE(0x1221, 0x3234)}, //informacao obtida usando "lsusb" no terminal
	{} /*entrada terminal*/
};
MODULE_DEVICE_TABLE(usb, pen_table);


// usb_driver
static struct usb_driver pen_driver = {
	.name = "Henrique-USB Stick Driver",
	.id_table = pen_table,//usb_device_id
	.probe = pen_probe,
	.disconnect = pen_disconnect,
};

static int __init pen_init(void){
	int ret = -1;
	printk(KERN_SOH "[*] construtor do driver");
	printk(KERN_SOH "\tRegistrando driver com kernel");
	ret = usb_register(&pen_driver);
	printk(KERN_SOH  "\tRegistro completo");
	return ret;
}

static void __exit pen_exit(void){
	//deregister
	printk(KERN_SOH "[*] Desconstrutor do driver");
	usb_deregister(&pen_driver);
	printk(KERN_SOH "\tregistro cancelado!");
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HenriqueAnnicchino");
MODULE_DESCRIPTION("USB Pen Drive registration");
