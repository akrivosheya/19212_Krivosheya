definition rodst_short;
// #begin# Machine generated header. Do not alter or delete this line.

include ".\\rodst_short.vdm_dm"
// #end# Do not alter or delete this line.

type ��� = atom( ���, ��� );

class �������;

class �������
  ���:		atom;
  ���:		���;
  ������: �������;
  ����: set of ������� := �������{};      
  ��������:  set of ������� := �������{};
constraints
    �_���: ��� != ������.���;
    �_������: ������.������ = $;
//    �_����: ���� = ������.����;
end;

relation ������ ( ���: �������; ����: �������)
sym;
end;

end.
