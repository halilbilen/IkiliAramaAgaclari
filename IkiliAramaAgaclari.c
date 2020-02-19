#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int i=0,derinlik=0,t1=0,t2=0,t3=0;
struct kelimeler
{
	char kelime[100];
    int tane;
    struct kelimeler *sol, *sag;
};
struct kelimeler *temp=NULL;
struct kelimeler* ek(struct kelimeler* eks, char k[])
{
    if (eks == NULL)
	{
		struct kelimeler *ekle;
        ekle =  (struct kelimeler *)malloc(sizeof(struct kelimeler));
        strcpy(ekle->kelime,k);
        ekle->tane=1;
        ekle->sol = NULL;
	    ekle->sag = NULL;
        return ekle;
	}
    if (strcmp(eks->kelime,k)>0)
    {
    	eks->sol  = ek(eks->sol, k);
	}
	else if(strcmp(eks->kelime,k)==0)
	{
		eks->sol  = ek(eks->sol, k);
	}
    else
    {
        eks->sag = ek(eks->sag, k);
	}
    return eks;
}
void siraliyazdir(struct kelimeler *kok)
{
    if (kok != NULL)
    {
        siraliyazdir(kok->sol);
        if(kok->tane>=1)
        {
        	t1++;
        	printf("%s Tane=%d\n", kok->kelime,kok->tane);
		}
        siraliyazdir(kok->sag);
    }
}
void yazdir(struct kelimeler *kok)
{
    if (kok != NULL)
    {
    	yazdir(kok->sol);
    	if(kok->tane>=1)
        {
        	t3++;
        	printf("%s Tane=%d\n", kok->kelime,kok->tane);
		}
		
    	yazdir(kok->sag);
        
		
		
    }
}
int aras2(struct kelimeler *kok,char kelimes[])
{
	int y=0;
	temp=kok;
	if(temp==NULL)
	{
		return 0;
	}
	while(temp!=NULL)
	{
		if(strcmp(temp->kelime,kelimes)!=0)
		{
			if(strcmp(temp->kelime,kelimes)>0)
			{
				temp=temp->sol;
			}
			else
			{
				temp=temp->sag;
			}
			y=0;
		}
		else
		{
			temp->tane++;
			return 1;
		}
	}
	if(y==0)
	{
		return 0;
	}
}
void aras(struct kelimeler *kok,char ara[])
{
	struct kelimeler *temp;
	temp=kok;
	if(temp==NULL)
	{
		printf("Liste bos\n");
	}
	while(strcmp(temp->kelime,ara)!=0)
	{
		
		if(temp!=NULL)
		{
			derinlik++;
			if(strcmp(temp->kelime,ara)>0)
			{
				temp=temp->sol;
			}
			else
			{
				temp=temp->sag;
			}
		}
		if(temp==NULL)
		{
			printf("\n");
			printf("Bulunmadi\n");
			return;
		}
	}
	printf("%s Derinlik=%d Tane=%d\n",temp->kelime,derinlik,temp->tane);
}
int dugumsayisi(struct kelimeler *kok)
{
	if(kok==NULL)
	{
		return 0;
	}
	else
	{
		return dugumsayisi(kok->sol)+1+dugumsayisi(kok->sag);
	}
}
int yukseklik(struct kelimeler *kok) 
{
    if(kok == NULL)
    {
      	return 0;
    }
    else
    {
    	int solu,sagu;
    	solu=yukseklik(kok->sol);
    	sagu=yukseklik(kok->sag);
    	if(sagu>solu)
    	{
    		return sagu+1;
		}
		else
		{
			return solu+1;
		}
	}
}
int main()
{
	int x,secim;
    struct kelimeler *kok = NULL;
    char kelimes[100],ara[100];
	FILE *oku;
	oku=fopen("a.txt","r");
	while(!feof(oku))
	{
		fscanf(oku,"%s",&kelimes);
		x=aras2(kok,kelimes);
		if(x==0)
		{
			kok=ek(kok,kelimes);
		}
		i++;
	}
	printf("Toplamda %d kelime dosyadan okundu ve ikili arama agacina kaydedildi.\n",i);
	x=dugumsayisi(kok);
	printf("Ikili arama agacinin dugum sayisi=%d\n",x);
	x=yukseklik(kok);
	printf("Ikili arama agacinin derinligi=%d\n",x-1);
	printf("\n");
	while(1)
	{
		printf("1 - Farkli kelimeleri yazdir\n");
		printf("2 - Farkli kelimeleri alfabetik yazdir\n");
		printf("3 - Kelime aramasi yap\n");
		printf("4 - Cikis yap\n");
		printf("Seciminiz=");
		scanf("%d",&secim);
		printf("\n");
		if(secim==1)
		{
			yazdir(kok); 
			printf("Toplamda %d kelime yazdirildi\n",t3);
		}
		else if(secim==2)
		{
            printf("Siralanmis \n");
            siraliyazdir(kok);
            printf("\n");
            printf("Toplam %d kelime alfabetik siralandi\n",t1);
		}
		else if(secim==3)
		{
			printf("Aranacak Kelime Girin=");
	        scanf("%s",&ara);
	        aras(kok,ara);
		}
		else
		{
			printf("Cikis komutu verildi, program kapatiliyor. . .");
			exit(0);
		}
	}
    return 0;
}
