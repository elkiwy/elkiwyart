

void to_lowercase(char *str, char *target, size_t tsize) {
  for (size_t i = 0; i < tsize; i++) {
    target[i] = str[i];
    if (target[i] == '\0') {
      break;
    }
    if (target[i] == ' ') {
      target[i] = '_';
    } else {
      target[i] = tolower(target[i]);
    }
  }
  target[tsize - 1] = '\0';
}


char* formattedString(char* format, char* s1){
	int size = strlen(s1)+strlen(format)+1;
	char* s = malloc(sizeof(char)*size);
	sprintf(s, format, s1);
	return s;
}



char* stringRepl(char* s, char old, char new){
	char* news = malloc(sizeof(char)*strlen(s)+1);
	int len = strlen(s);
	for (int i=0; i<len; ++i){
		if (s[i] == old){
			news[i] = new;
		}else{
			news[i] = s[i];
		}
	}
	news[len] = 0;
	return news;
}

void logStr(char* s){
	printf("=>log string %s\n", s); fflush(stdout);
}


char* clickableImg(char* src, char* class){
	char* format = "<a href='../media/img/%s'><img class='%s' src='../media/img/%s'/></a>";
	int size = strlen(format) + strlen(src)*2 + strlen(class) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, src, class, src);
	return buff;
}
