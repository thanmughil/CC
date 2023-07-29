#include <stdio.h>
#include <stdlib.h>

char ui[3][3];
int combx[10],combo[10],cmcnt=0,om,cm;

int chkwin(int a[]);

void print_board()
{
  system("timeout 1 > NUL");
  system("cls");
  printf("\n-------------\n");
  for(int i=0;i<3;i++)
  {
    printf("|");
    for(int j=0;j<3;j++)
      printf(" %c |",ui[i][j]);

    printf("\t\t");
    for(int j=1;j<4;j++)
    {
      if(combx[(3*i)+j]||combo[(3*i)+j]||chkwin(combx)||chkwin(combo)) printf("   ");
      else printf("%d  ",3*i+j);
    }
    printf("\n-------------\n");
  }
  printf("\n");
}

void init()
{
  cmcnt=cm=om=0;
  for(int i=0;i<10;i++)
    combx[i]=combo[i]=0;

  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
      ui[i][j] = ' ';
  }
}

void inpx()
{
  printf("\nEnter Position to Insert X : ");
  scanf("%d",&om);

  if(om<1||om>9)
  {
    printf("\nOut of Range!\n");
    inpx();
  }
  else if(combx[om]||combo[om])
  {
    printf("\nCannot Overwrite!\n");
    inpx();
  }
  else
  {
    combx[om]=1;
    ui[(om-1)/3][(om-1)%3] = 'X';
    return;
  }
}

void inpo(int ch)
{
  if(combx[ch]||combo[ch]||ch==0) inpo((ch+1)%10);
  else
  {
    combo[ch]=1;
    cm = ch;
    ui[(ch-1)/3][(ch-1)%3] = 'O';
    return;
  }
}

int chkwin(int a[])
{
  if((a[1]&&a[4]&&a[7])||(a[2]&&a[5]&&a[8])||(a[3]&&a[6]&&a[9]))
    return 1;

  if((a[1]&&a[2]&&a[3])||(a[4]&&a[5]&&a[6])||(a[7]&&a[8]&&a[9]))
    return 1;

  if((a[1]&&a[5]&&a[9])||(a[3]&&a[5]&&a[7]))
    return 1;
}

int pldraw2(int x)
{
  switch(x)
  {
    case 1:      if(combx[6]&&!combx[3]) return 3;
            else if(combx[8]&&!combx[7]) return 7;
            break;

    case 2:      if(combx[4]&&!combx[2]) return 1;
            else if(combx[6]&&!combx[3]) return 3;
            else if(combx[7]&&!combx[1]) return 1;
            else if(combx[9]&&!combx[3]) return 3;
            break;

    case 3:      if(combx[5]&&!combx[7]) return 7;
            else if(combx[5]&&!combx[9]) return 9;
            else if(combx[4]&&!combx[1]) return 1;
            else if(combx[8]&&!combx[9]) return 9;
            break;

    case 4:      if(combx[2]&&!combx[1]) return 1;
            else if(combx[8]&&!combx[7]) return 7;
            else if(combx[3]&&!combx[1]) return 1;
            else if(combx[9]&&!combx[7]) return 7;
            break;

    case 5: break;

    case 6:      if(combx[2]&&!combx[3]) return 3;
            else if(combx[8]&&!combx[9]) return 9;
            else if(combx[1]&&!combx[3]) return 3;
            else if(combx[7]&&!combx[9]) return 9;
            break;

    case 7:      if(combx[5]&&!combx[3]) return 3;
            else if(combx[5]&&!combx[9]) return 9;
            else if(combx[2]&&!combx[1]) return 1;
            else if(combx[6]&&!combx[9]) return 9;
            break;

    case 8:      if(combx[4]&&!combx[7]) return 7;
            else if(combx[6]&&!combx[9]) return 9;
            else if(combx[1]&&!combx[7]) return 7;
            else if(combx[3]&&!combx[9]) return 9;
            break;

    case 9:      if(combx[5]&&!combx[3]) return 3;
            else if(combx[5]&&!combx[7]) return 7;
            else if(combx[2]&&!combx[3]) return 3;
            else if(combx[4]&&!combx[7]) return 7;
            break;
  }
  return 0;
}

int plfor(int x)
{
  switch(x)
  {
    case 1:      if(!combo[3]&&combo[2]&&!combx[3]) return 3;
            else if(!combo[2]&&combo[3]&&!combx[2]) return 2;
            else if(!combo[4]&&combo[7]&&!combx[4]) return 4;
            else if(!combo[7]&&combo[4]&&!combx[7]) return 7;
            else if(!combo[5]&&combo[9]&&!combx[5]) return 5;
            else if(!combo[9]&&combo[5]&&!combx[9]) return 9;
            break;

    case 2:      if(!combo[1]&&combo[3]&&!combx[1]) return 1;
            else if(!combo[3]&&combo[1]&&!combx[3]) return 3;
            else if(!combo[5]&&combo[8]&&!combx[5]) return 5;
            else if(!combo[8]&&combo[5]&&!combx[8]) return 8;
            break;

    case 3:      if(!combo[1]&&combo[2]&&!combx[1]) return 1;
            else if(!combo[2]&&combo[1]&&!combx[2]) return 2;
            else if(!combo[5]&&combo[7]&&!combx[5]) return 5;
            else if(!combo[7]&&combo[5]&&!combx[7]) return 7;
            else if(!combo[6]&&combo[9]&&!combx[6]) return 6;
            else if(!combo[9]&&combo[6]&&!combx[9]) return 9;
            break;

    case 4:      if(!combo[1]&&combo[7]&&!combx[1]) return 1;
            else if(!combo[7]&&combo[1]&&!combx[7]) return 7;
            else if(!combo[5]&&combo[6]&&!combx[5]) return 5;
            else if(!combo[6]&&combo[5]&&!combx[6]) return 6;
            break;

    case 5:      if(!combo[3]&&combo[7]&&!combx[3]) return 3;
            else if(!combo[7]&&combo[3]&&!combx[7]) return 7;
            else if(!combo[4]&&combo[6]&&!combx[4]) return 4;
            else if(!combo[6]&&combo[4]&&!combx[6]) return 6;
            else if(!combo[2]&&combo[8]&&!combx[2]) return 2;
            else if(!combo[8]&&combo[2]&&!combx[8]) return 8;
            else if(!combo[1]&&combo[9]&&!combx[1]) return 1;
            else if(!combo[9]&&combo[1]&&!combx[9]) return 9;
            break;

    case 6:      if(!combo[9]&&combo[3]&&!combx[9]) return 9;
            else if(!combo[3]&&combo[9]&&!combx[3]) return 3;
            else if(!combo[5]&&combo[4]&&!combx[5]) return 5;
            else if(!combo[4]&&combo[5]&&!combx[4]) return 4;
            break;

    case 7:      if(!combo[1]&&combo[4]&&!combx[1]) return 1;
            else if(!combo[4]&&combo[1]&&!combx[4]) return 4;
            else if(!combo[5]&&combo[3]&&!combx[5]) return 5;
            else if(!combo[3]&&combo[5]&&!combx[3]) return 3;
            else if(!combo[8]&&combo[9]&&!combx[8]) return 8;
            else if(!combo[9]&&combo[8]&&!combx[9]) return 9;
            break;

    case 8:      if(!combo[9]&&combo[7]&&!combx[9]) return 9;
            else if(!combo[7]&&combo[9]&&!combx[7]) return 7;
            else if(!combo[5]&&combo[2]&&!combx[5]) return 5;
            else if(!combo[2]&&combo[5]&&!combx[2]) return 2;
            break;

    case 9:      if(!combo[1]&&combo[5]&&!combx[1]) return 1;
            else if(!combo[5]&&combo[1]&&!combx[5]) return 5;
            else if(!combo[6]&&combo[3]&&!combx[6]) return 6;
            else if(!combo[3]&&combo[6]&&!combx[3]) return 3;
            else if(!combo[8]&&combo[7]&&!combx[8]) return 8;
            else if(!combo[7]&&combo[8]&&!combx[7]) return 7;
            break;
  }
  return 0;
}

int pldraw(int y)
{
  switch(y)
  {
    case 1:      if(!combx[3]&&combx[2]&&!combo[3]) return 3;
            else if(!combx[2]&&combx[3]&&!combo[2]) return 2;
            else if(!combx[4]&&combx[7]&&!combo[4]) return 4;
            else if(!combx[7]&&combx[4]&&!combo[7]) return 7;
            else if(!combx[5]&&combx[9]&&!combo[5]) return 5;
            else if(!combx[9]&&combx[5]&&!combo[9]) return 9;
            break;

    case 2:      if(!combx[1]&&combx[3]&&!combo[1]) return 1;
            else if(!combx[3]&&combx[1]&&!combo[3]) return 3;
            else if(!combx[5]&&combx[8]&&!combo[5]) return 5;
            else if(!combx[8]&&combx[5]&&!combo[8]) return 8;
            break;

    case 3:      if(!combx[1]&&combx[2]&&!combo[1]) return 1;
            else if(!combx[2]&&combx[1]&&!combo[2]) return 2;
            else if(!combx[5]&&combx[7]&&!combo[5]) return 5;
            else if(!combx[7]&&combx[5]&&!combo[7]) return 7;
            else if(!combx[6]&&combx[9]&&!combo[6]) return 6;
            else if(!combx[9]&&combx[6]&&!combo[9]) return 9;
            break;

    case 4:      if(!combx[1]&&combx[7]&&!combo[1]) return 1;
            else if(!combx[7]&&combx[1]&&!combo[7]) return 7;
            else if(!combx[5]&&combx[6]&&!combo[5]) return 5;
            else if(!combx[6]&&combx[5]&&!combo[6]) return 6;
            break;

    case 5:      if(!combx[3]&&combx[7]&&!combo[3]) return 3;
            else if(!combx[7]&&combx[3]&&!combo[7]) return 7;
            else if(!combx[4]&&combx[6]&&!combo[4]) return 4;
            else if(!combx[6]&&combx[4]&&!combo[6]) return 6;
            else if(!combx[2]&&combx[8]&&!combo[2]) return 2;
            else if(!combx[8]&&combx[2]&&!combo[8]) return 8;
            else if(!combx[1]&&combx[9]&&!combo[1]) return 1;
            else if(!combx[9]&&combx[1]&&!combo[9]) return 9;
            break;

    case 6:      if(!combx[9]&&combx[3]&&!combo[9]) return 9;
            else if(!combx[3]&&combx[9]&&!combo[3]) return 3;
            else if(!combx[5]&&combx[4]&&!combo[5]) return 5;
            else if(!combx[4]&&combx[5]&&!combo[4]) return 4;
            break;

    case 7:      if(!combx[1]&&combx[4]&&!combo[1]) return 1;
            else if(!combx[4]&&combx[1]&&!combo[4]) return 4;
            else if(!combx[5]&&combx[3]&&!combo[5]) return 5;
            else if(!combx[3]&&combx[5]&&!combo[3]) return 3;
            else if(!combx[8]&&combx[9]&&!combo[8]) return 8;
            else if(!combx[9]&&combx[8]&&!combo[9]) return 9;
            break;

    case 8:      if(!combx[9]&&combx[7]&&!combo[9]) return 9;
            else if(!combx[7]&&combx[9]&&!combo[7]) return 7;
            else if(!combx[5]&&combx[2]&&!combo[5]) return 5;
            else if(!combx[2]&&combx[5]&&!combo[2]) return 2;
            break;

    case 9:      if(!combx[1]&&combx[5]&&!combo[1]) return 1;
            else if(!combx[5]&&combx[1]&&!combo[5]) return 5;
            else if(!combx[6]&&combx[3]&&!combo[6]) return 6;
            else if(!combx[3]&&combx[6]&&!combo[3]) return 3;
            else if(!combx[8]&&combx[7]&&!combo[8]) return 8;
            else if(!combx[7]&&combx[8]&&!combo[7]) return 7;
            break;
  }
  return 0;
}

int playopp()
{
  int x;
  if(++cmcnt==1)
  {
    if(combx[5]) return ++cm;
    else return 5;
  }
  else
  {
    if((x = plfor(cm))!=0) return x;
    else if((x = pldraw(om))!=0) return x;
    else if((x = pldraw2(om))!=0) return x;
    else return cm;
  }
}

void play()
{
  int i=1;
  char ch;
  print_board();

  while(i<=9)
  {
    (i%2==0)?inpo(playopp()):inpx();
    if(chkwin(combx)||chkwin(combo))
    {
      print_board();
      if(i%2==0)
      {
        printf("\n\nO is the Winner!");
        return;
      }
      else
      {
        printf("\n\nX is the Winner!");
        return;
      }
    }
    if(i%2==0) print_board();
    i++;
  }
  for(int j=1;j<10;j++)
  {
    if (combo[j]==0&&combx[j]==0)
    {
      combo[j]=1;
      cm = j;
      ui[(j-1)/3][(j-1)%3] = 'O';
    }
  }
  print_board();
  printf("\n\nMatch Drawn!");
  return;
}

int main()
{
  char ch = 'Y';
  while(ch=='Y')
  {
    init();
    play();
    printf("\n\nPlay Again? (Y/N) : ");
    scanf("\n%c",&ch);
  }
  return 0;
}
