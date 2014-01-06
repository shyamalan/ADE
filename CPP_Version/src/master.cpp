bool Setup();

bool loop();

int main(){
	bool flag = true;
	flag = Setup();
	
	while(flag){
		
		flag = loop();
	}
	return 0;
}
