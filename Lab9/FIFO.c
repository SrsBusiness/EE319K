

unsigned char data[16];
int put = 15;
int get = 15;
unsigned char FIFO_get(){
	unsigned char result = data[get];
	get = (--get) % 16;
	return result;
}	
void FIFO_put(unsigned char digit){
	data[put] = digit;
	put = (--put) % 16;
}
int FIFO_is_empty (){
	return get == put;
}
