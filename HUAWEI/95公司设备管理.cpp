//公司设备管理系统，某公司有许多员工和设备，每个员工有一个8位数字组成的ID，
//每台设备有个小于等于20位由数字和字母组成的设备号。
//每个员工可以拥有多台设备，但是每台设备只能分配给一个员工使用。
//
//输入四个数a, b, c, d
//a : 给这个系统添加多少台设备
//b : 从这个系统中删除多少台设备
//c : 添加设备和员工的对应关系
//d : 删除设备和员工的对应关系
//	之后是由这4个参数控制的输入序列
//	a行设备编号，若添加失败则输出"add computers error:" + 设备号；成功不输出
//	b行删除设备的编号，若删除失败则输出"remove computers error:" + 设备号；成功不输出
//	c行要分配给员工的设备，若添加失败则输出“assign computer error : 
//	” + 设备号 + “_” + 员工号；成功不输出
//	d行要删除分配给员工的设备，若删除失败则输出:
//	"remover computer from worker error:" + 设备号 + “_” + 员工号；成功不输出
//	最后要求输出总共的设备数目和排序输出员工和设备的对应关系(员工号 + "_" + 设备号)
//	（先按照员工号进行排序，若员工有多台设备，则再按照设备号进行排序）。
//	如输入
//	3 2 2 1
//	SN001
//	SN002
//	SN003
//	SN003
//	SN004
//	SN002 12345678
//	SN001 12345678
//	SN001 12345678
//	输出：
//	remove computers error : SN004
//	1
//	12345678_SN002
