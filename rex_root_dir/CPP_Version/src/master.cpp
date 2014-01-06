
bool setup();

bool loop();


int main(){
	bool flag = true;
	flag = setup();
	
	while(flag){
		
		flag = loop();
	}
	return 0;
}
