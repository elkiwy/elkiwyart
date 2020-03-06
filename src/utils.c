

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


char* clickableImg(char* src, char* class, char* style){
#ifdef CREATING_THUMBNAILS
	char* format;
	if (strcasecmp(src + strlen(src) - 4, ".png") == 0) {
		format = "<a href='../media/img/%s'><img class='%s' style='%s' src='../media/thumb/%s'/></a>";
	}else{
		format = "<a href='../media/img/%s'><img class='%s' style='%s' src='../media/img/%s'/></a>";
	}
	int size = strlen(format) + strlen(style) + strlen(src)*2 + strlen(class) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, src, class, style, src);
	return buff;
#else
	char* format = "<a href='../media/img/%s'><img class='%s' style='%s' src='../media/img/%s'/></a>";
	int size = strlen(format) + strlen(style) + strlen(src)*2 + strlen(class) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, src, class, style, src);
	return buff;
#endif
}



char* formatString(char* format, int n, ...){
	va_list args;
	va_list args_copy;
	char* strings[n];
	int size = 0;
	va_start(args, n);
	va_copy(args_copy, args);
	for (int i=0; i<n; ++i){
		strings[i] = va_arg(args, char*);
		size += strlen(strings[i]);
	}
	size += strlen(format) + 1;
	char* buff = malloc(sizeof(char) * size);
	vsprintf(buff, format, args_copy);
	va_end(args);
	return buff;
}

char* joinStrings(int n, ...){
	va_list args;
	int size = 0;
	char* strings[n];

	//Extract args
	va_start(args, n);
	for (int i=0; i<n; ++i){
		strings[i] = va_arg(args, char*);
		size += strlen(strings[i]);
	}

	//Build the string
	char* buff = malloc(sizeof(char) * (size + 1));
	strcpy(buff, strings[0]);
	for (int i=1; i<n; ++i){
		strcat(buff, strings[i]);
	}
	return buff;
}


char* joinStringsArr(int n, char** arr){
	int size = 0;

	//Extract args
	for (int i=0; i<n; ++i){
		size += strlen(arr[i]);
	}

	//Build the string
	char* buff = malloc(sizeof(char) * (size + 1));
	strcpy(buff, arr[0]);
	for (int i=1; i<n; ++i){
		strcat(buff, arr[i]);
	}
	return buff;
}



