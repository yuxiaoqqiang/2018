package test1;
import java.util.Stack;

/**Main类，打印各个算法的结果
* @author dyl
*
*/
class Count{
	int result;
	int xiabiao[]=null;//访问的下标
	public static void main(String[] args){
		Graph graph=new Graph();
		System.out.println("----------------罗马尼亚问题---------------");
		System.out.println("1、深度优先搜索");
		DFS dfs=new DFS();
		dfs.DF_Search(graph,5,12);
		System.out.println("2、迭代加深的搜索");
		IDS ids=new IDS();
		ids.IDS_Search(graph,5,12,15);//深度设15
		System.out.println("3、一致代价搜索");
		UCS ucs=new UCS(graph,5,12);
		System.out.println("4、A*搜索");
		AXing aXing=new AXing();
		aXing.A_Search(graph, graph.H,5,12);//0-15即Arad到达Hirsova
	}
	/**打印
	* @param g:图
	* @param stack：栈
	*/
	public void show(Graph g,Stack stack){
		if(stack.size()==0){
			System.out.println("路径搜索失败");
			return;
		}
		result=0;
		System.out.print("访问的下标： ");
		for(int i =0; i < stack.size(); i++){
			System.out.print("-->"+stack.get(i));
		}
		System.out.print("\n访问过程： ");
		xiabiao=new int[stack.size()];
		if(stack.isEmpty()){
			System.out.println("搜索失败");
		}
		else{
			for(int i =0; i < stack.size(); i++){
				System.out.print("-->"+g.cities[(Integer) stack.get(i)]);
			}
			for(int i =0; i < stack.size()-1; i++){
				result+=g.path[(Integer) stack.get(i)][(Integer) stack.get(i+1)];
			}
			System.out.println("\n总长度为："+result+"\n");
			g.markInit();//清空访问
		}
	}
}
/**图类
* @author dyl
*
*/
class Graph{
	public int path[][]=new int[][]{
	{0,75,10000,118,140,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000},
	{75,0,71,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000},
	{10000,71,0,10000,151,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000},
	{118,10000,10000,0,10000,111,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000},
	{140,10000,151,10000,0,10000,80,99,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,111,10000,0,10000,10000,70,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,80,10000,0,10000,10000,10000,146,97,10000,10000,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,99,10000,10000,0,10000,10000,10000,10000,211,10000,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,10000,70,10000,10000,0,75,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,10000,10000,10000,10000,75,0,120,10000,10000,10000,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,10000,10000,146,10000,10000,120,0,138,10000,10000,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,10000,10000,97,10000,10000,10000,138,0,101,10000,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,10000,10000,10000,211,10000,10000,10000,101,0,90,85,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,90,0,10000,10000,10000,10000,10000,10000},
	{10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,85,10000,0,98,10000,142,10000,10000},
	{10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,98,0,86,10000,10000,10000},
	{10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,86,0,10000,10000,10000},
	{10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,142,10000,10000,0,92,10000},
	{10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,92,0,87},
	{10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000,87,0}};
	public int[]H=new int[]{366,374,380,329,253,244,193,176,241,242,160,100,0,77,80,151};//启发式函数
	public String[] cities=new String[]{"Arad","Zerind","Oradea","Timisoara","Sibiu","Lugoj",
			"Rimnicu Vilcea","Fagaras","Mehadia","Drobeta","Craiova","Pitesti","Bucharest","Giurgiu","Urziceni","Hirsova",
			"Eforie","Vaslui","Isi","Neamt"};//城市名
	public int[]mark=new int[20];//访问标记
	public Graph(){//得到数据
		markInit();
	}
 
	/**
	 * 访问标志初始化
	 */
	public void markInit(){
		for(int i =0; i < mark.length; i++){
			mark[i]=0;
		}
	}
	/**第一个孩子
	* @param g
	* @param start
	* @return -1表示一个孩子都没有
	*/
	public int getFirstVex(int start){
		if(start>=0&&start<path.length){
			for(int j =0; j < path.length; j++)
				if(path[start][j]<10000&&path[start][j]>0)//有关系
					return j;
		}
		return-1;
	}
 
	/**下一个孩子
	* @param start
	* @param w
	* @return 表示图G中顶点i的第j个邻接顶点的下一个邻接顶点
	* 返回-1，表示后面没有邻接点了
	*/
	public int getNextVex(int start,int w){
		if(start>=0&&start<path.length&&w>=0&&w<path.length){
			for(int i = w+1; i < path.length; i++)
				if(path[start][i]<10000&&path[start][i]>0)
					return i;
		}
		return-1;
	}
	public int getNumber(){
		return path.length;
	}
}