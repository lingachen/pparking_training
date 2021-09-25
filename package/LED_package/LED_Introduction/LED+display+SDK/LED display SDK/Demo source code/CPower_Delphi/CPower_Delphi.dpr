program CPower_Delphi;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  cpower in 'cpower.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
