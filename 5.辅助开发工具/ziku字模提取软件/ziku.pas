unit ziku;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, ComCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Label1: TLabel;
    BitBtn1: TBitBtn;
    Memo1: TMemo;
    Label2: TLabel;
    Label5: TLabel;
    Animate1: TAnimate;
    Timer1: TTimer;
    Memo2: TMemo;
    Label3: TLabel;
    SpeedButton1: TSpeedButton;
    Timer2: TTimer;
    Label4: TLabel;
    Memo3: TMemo;
    Label6: TLabel;
    procedure BitBtn1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation
uses math;
var avifilename:byte;
{$R *.DFM}
 function translate(str:string):string;
var st:string;
       num:integer;
       trans:string;
 begin
        st:=str;
        trans:='';
       for num:=1 to 4 do
       begin
         case  st[num] of
                        '0':trans:=trans+'                ';
                        '1':trans:=trans+'            11';
                        '2':trans:=trans+'        11    ';
                        '3':trans:=trans+'        1111';
                        '4':trans:=trans+'    11        ';
                        '5':trans:=trans+'    11    11';
                        '6':trans:=trans+'    1111    ';
                        '7':trans:=trans+'    111111';
                        '8':trans:=trans+'11            ';
                        '9':trans:=trans+'11        11';
                        'A':trans:=trans+'11    11    ';
                        'B':trans:=trans+'11    1111';
                        'C':trans:=trans+'1111        ';
                        'D':trans:=trans+'1111    11';
                        'E':trans:=trans+'111111    ';
                        'F':trans:=trans+'11111111';
                                              end;


              end;
          translate:=trans;
  end;
procedure  TForm1.BitBtn1Click(Sender:  TObject);

var  hzk16:file  of  char  ;
        i:array[1..32]  of  char;
        j:longint;
        p:array[1..32] of byte;
        q:array[1..16] of longint;
        k:string;
        w:word;
        count:longint;
        n:integer;
        m:integer;
        sss:string;
        canshu:longint;
        stemp:string;
begin
       assignfile(hzk16,'hzk16');
      //assignfile(hzk16,'hzk24h');
          FileMode  :=  0;
        reset(hzk16);
        k:=edit1.text;

        j:=((ord(k[1])-161)*94+(ord(k[2])-161))*32;
      seek(hzk16,j);
    memo1.Text:='';
    memo2.text:='';
    memo3.text:='';
    memo1.Lines.add(' ');
    n:=1;
    label5.caption:='';
    sss:='';
    for  count:=1  to  32  do
    begin
        read(hzk16,i[n]);
        stemp:=inttohex(ord(i[n]),2)+'H';
        if ((n mod 8)<>0 )then stemp:=stemp+',';
        if stemp[1]>'9' then stemp:='0'+stemp;
        sss:=sss+stemp;
        if n mod 8=0 then sss:=sss+char(13)+char(10);
        label5.caption:=label5.caption+inttohex(ord(i[n]),2);
        n:=n+1;
        if  (n  mod  2=1)  then
        begin
        memo1.Lines.Add(label5.caption+'        '+translate(label5.caption));
        label5.caption:='';
        end;
    end;
       memo2.text:=sss;
     for n:=1 to 32 do
     begin
          if n mod 2=1 then p[((n+1) div 2)]:=ord(i[n]);
          if n mod 2=0 then p[((n) div 2)+16]:=ord(i[n]);

     end;
         for n:= 1 to 16 do
            begin
                 q[n]:=p[n]*256+p[n+16];

            end;
           sss:='';
        for m:=1 to 16 do
        begin
            w:=0;
              case m  of
                1: count:=$8000;
                2: count:=$4000;
                3:count:=$2000;
                4:count:=$1000;
                5:count:=$800;
                6:count:=$400;
                7:count:=$200;
                8:count:=$100;
                9:count:=$80;
                10:count:=$40;
                11:count:=$20;
                12:count:=$10;
                13:count:=$8;
                14:count:=$4;
                15:count:=$2;
                16:count:=$1;
                  end;
        for   n:=1 to 16 do
        begin

                case  n of
                1: canshu:=$8000;
                2: canshu:=$4000;
                3:canshu:=$2000;
                4:canshu:=$1000;
                5:canshu:=$800;
                6:canshu:=$400;
                7:canshu:=$200;
                8:canshu:=$100;
                9:canshu:=$80;
                10:canshu:=$40;
                11:canshu:=$20;
                12:canshu:=$10;
                13:canshu:=$8;
                14:canshu:=$4;
                15:canshu:=$2;
                16:canshu:=$1;
                  end;
            if (q[n] and count)<>0 then
            begin
           w:=w+ canshu;
             end;

         end;
          stemp:=copy(inttohex(w,4),1,2)+'H';
         stemp:=stemp+',';
        if stemp[1]>'9' then stemp:='0'+stemp;
        sss:=sss+stemp;
          stemp:=copy(inttohex(w,4),3,2)+'H';
        if ((2*m mod 8)<>0 )then stemp:=stemp+',';
        if stemp[1]>'9' then stemp:='0'+stemp;
        sss:=sss+stemp;

        if m mod 4=0 then sss:=sss+char(13)+char(10);
        label5.caption:=label5.caption+inttohex(ord(i[n]),2);


                     end;
             memo3.text:=sss;        
        system.close(hzk16);
end;

procedure TForm1.Timer1Timer(Sender: TObject);

begin
case avifilename of
   1: animate1.commonavi:=avicopyfile;
   2: animate1.commonavi:=avicopyfiles;
   3: animate1.commonavi:=aviemptyrecycle;
   4: animate1.commonavi:=avifindcomputer;
   5: animate1.commonavi:=avifindfolder;
   6: animate1.commonavi:=avirecyclefile;
end;
avifilename:=avifilename+1;
if avifilename=7 then avifilename:=1;
 animate1.active:=true;

end;

procedure TForm1.FormCreate(Sender: TObject);
begin
avifilename:=1;
animate1.active:=true;
bitbtn1.click;
end;

procedure TForm1.Timer2Timer(Sender: TObject);
begin
 speedbutton1.Caption:=timetostr(now);
end;

end.
