using System.Reflection;
using System.Runtime.CompilerServices;

//
// ����ǭ��Ǣ���ۡ�ǿǦ��Ǣ�vǭ�����ڡu�������}ǭ����ǽ��
// �ˡ���ǳǿǹ������Ǧ�ġC�vǫ�������eǡ�ˡ�����Ǧǹ������ǫ���ޡ����ۡ�ǿ
// ǭ��ǽǣǦ�������ڡu�C�v
//
[assembly: AssemblyTitle("")]
[assembly: AssemblyDescription("")]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany("")]
[assembly: AssemblyProduct("")]
[assembly: AssemblyCopyright("")]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]		

//
// Ǣ���ۡ�ǿǦ�����Ƿ�����ڡu��������ǽ�� 4 ǫ��Ǧ���^��:
//
//      �䡼��Ƿ
//      Ǥ�����Ƿ 
//      �����~ǹ���Ƿǯ��
//      ����ǧǡǯ��
//
// �ĪY��������ǫǧ�}�Ρ������eǡ��Ǧ�v�����~ǹ��������ǭ���¡C������ǧǡǯ�ơC�|ǯ�ԡC�������~ǹ���Ƿǯ�ơC�|Ǧ������������Ǧ�v��ǩǵǩ�}������Ǥ
// ���Q���Ρ�Ƿ��ǭ���� '*':

[assembly: AssemblyVersion("1.0.*")]

//
// ��ǣǧ��Ǣ���ۡ�ǿǵ������ǡ�������|���ۡ�ǫǧ�}��ǣ��ǭ����Ǧ��������ǹ�C�v����ǭ��Ǣ���ۡ�ǿ��ǡ���R��ǫ�������ڡu�v���ȡ���ǹǳ 
// Microsoft .NET Framework ����ǦǦ�C�v
//
// ��ǭ���������½����ˡ���ǹ����������������ǡ���R��������ǹ�C�v
//
// ��u�ݡ�
//   (*) �ɰr��Ǥ��ǫǧ�}������ǹ�v���ࡼ���ۡ�ǿ�~ǱǱ��Ǳ��ǡ�����v
//   (*) KeyName ������ǫ����Ƿ�����~��������ǳ����ü�a��Ǧ��
//      ǳ������ǩ������ǡǢ���ۡ�CSP)����Ǧ��������ǹ�C�vKeyFile ������ǫ�㡼��
//       ������ǹǦ������ǳ���v
//   (*) �ɰr��KeyFile ǯ�� KeyName ��Ǧǧǳ������ǫǧ�}�v���ࡼ
//       ǩ�u�ʩ���ǽ��Ǥ��ǻ��
//       (1) �ɰr�x�� CSP ����ǹ����������Ǧǵ KeyName�v���ࡼǭ����ǫ��������ǹ�C�v
//       (2) �ɰr��KeyName �~ǱǤ�I��ǧ��KeyFile Ǥ�I��v���ࡼ
//           KeyFile ����Ǧ��������ǹ���~����Ǧǵ CSP �����~�u������ǭ����ǫ��������ǹ�C�v
//   (*) ��ǣǤǤǵ�} KeyFile�v��ǹ��������ǭ���� sn.exe(��ǹ�¡���)��Ǧ����ǭ�BǷ�աC�v
//       ������ǫǧ�} KeyFile ���|�v��KeyFile Ǧ����Ǳ��������ǫ���ں�������
//       �ڡ�ǹ�˲ǹ��ǳ�v��ǳǤ
//       %Project Directory%\obj\<configuration>�C�vǻ���}���ɰr��KeyFile ��Ǳ����
//       ǫ���ڡ�ǹ��ǹ��ǳ�v������ǵǥ AssemblyKeyFile 
//       �ˡ�����ǫǧ�}��ǣ [assembly: AssemblyKeyFile("..\\..\\mykey.snk")]
//   (*) �C������Ǣ����ǡ�����|������Ǳǫ����ǳǧ�ܡC�ڡ�- ����ǭ���Ρ���ǫ�������ڡu�v���ȡ������� Microsoft .NET Framework
//       ����ǦǦ�C�v
//
[assembly: AssemblyDelaySign(false)]
[assembly: AssemblyKeyFile("")]
[assembly: AssemblyKeyName("")]
