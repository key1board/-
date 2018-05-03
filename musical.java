package hehe;

import java.awt.*;
import javax.swing.*;
import javax.sound.midi.*;
import java.util.*;
import java.awt.event.*;

public class SimpleGuil{
	JPanel mainPanel;
	ArrayList <JCheckBox> checkboxList;
	Sequencer sequencer;
	Sequence sequence;
	Track track;
	JFrame frame;
	
	//乐器的名称
	String[] instrumentNames = {"Bass Drum","Closed Hi-Hat","Open Hi-Hat","Acoustic Snare"
			,"Crash Cymbal","Hand Clap","High Tom","Hi Bongo","Maracas","Whistle","Low Conga"
			,"Cowbell","Vibraslap","Low-mid Tom","High Agogo","Open Hi Conga"};
	//实际乐器的关键字,例如35是bass,42是Closed Hi-Hat
	int[] instruments = {35,42,46,38,49,39,50,60,70,72,64,56,58,47,67,63};
	public static void main(String[] arg) {
		new SimpleGuil().buildGUI();
	}
	public void buildGUI() {
		frame = new JFrame("Cyber BeatBox");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		BorderLayout layout = new BorderLayout();
		//创建具有指定布局管理器的新缓冲JPanel
		JPanel background = new JPanel(layout);
		//创建一个占用空间但没有绘制的空边框,指定了上下左右的宽度
		background.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
		
		//创建一个存储对象都是checkboxlist对象的ArrayList
		checkboxList = new ArrayList<JCheckBox>();
		Box buttonBox = new Box(BoxLayout.Y_AXIS);     //创建一个从上到下布置的组件的box
		
		JButton start = new JButton("Start");
		start.addActionListener(new MyStartListener());
		buttonBox.add(start);
		
		JButton stop = new JButton("Stop");
		stop.addActionListener(new MyStopListener());
		buttonBox.add(stop);
		
		JButton upTempo = new JButton("Tempo Up");
		upTempo.addActionListener(new MyUpTempoListener());
		buttonBox.add(upTempo);
		
		JButton downTempo = new JButton("Tempo Down");
		downTempo.addActionListener(new MyDownTempoListencer());
		buttonBox.add(downTempo);
		
		Box nameBox = new Box(BoxLayout.Y_AXIS);
		for(int i=0;i<16;i++) { 
			//使用指定的文本字符串构造一个新的标签,其文本对其方式为左对齐
			nameBox.add(new Label(instrumentNames[i]));
		}
	
		background.add(BorderLayout.EAST,buttonBox);//将组件向左对齐
		background.add(BorderLayout.WEST,nameBox);//将组件向右对齐
		
		frame.getContentPane().add(background);
		//创建具有具有指定行数,列数的网格布局
		GridLayout grid = new GridLayout(16,16);
		grid.setVgap(1);  //将组件之间的垂直距离设定为指定值
		grid.setHgap(2);  //将组件之间的水平距离设置为指定值
		mainPanel = new JPanel(grid);
		//创建一个布置容器的边框布局,它可以调整容器组件的大小,使其符合北,南,东,西,中每个区域最多只能包含一个组件
		background.add(BorderLayout.CENTER,mainPanel);
		
		for(int i=0;i<256;i++) {//创建checkbox组,设定成未勾选的为false并加到Arraylist面板上
			//创建一个没有文本,没有图标并且最初未被选定的复选框
			JCheckBox c = new JCheckBox();
			c.setSelected(false);//设置按钮的状态,此方法不会触发ActionEvent
			checkboxList.add(c);
			mainPanel.add(c);
		}
		setUpMidi();
		
		frame.setBounds(50,50,300,300);
		frame.pack();
		frame.setVisible(true);
	}
	//MIDI程序设置代码
	public void setUpMidi() {
		try {
			sequencer = MidiSystem.getSequencer();//从指定的File获得MIDI序列
			sequencer.open();//打开设备,指示它现在应获取任何所需的系统资源然后开始运行
			sequence = new Sequence(Sequence.PPQ,4);
			track = sequence.createTrack();
			sequencer.setTempoInBPM(120);
		}
		catch(Exception ex) {}
	}
	//创建出16个元素的数组来存储一项乐器的值,如果该节应该要演奏,其值会是关键值,否则为0
	public void buildTrackAndStart() {
		int[] trackList = null;
		
		//清除旧的track做一个新的
		sequence.deleteTrack(track);
		track = sequence.createTrack();
		
		for(int i=0;i<instrumentNames.length;i++) {//对每个乐器都执行一次
			trackList = new int[16];
			
			int key = instruments[i];//设定代表乐器的关键字
			
			for(int j=0;j<16;j++) {//对每一拍执行一次
				JCheckBox jc = (JCheckBox)checkboxList.get(j +(16 * i));
				if(jc.isSelected()) {//如果有勾选,将关键字值放到数组的该位置上
					trackList[j] = key;
				}else {      //否则补0
					trackList[j] = 0;
					}
			}
			makeTracks(trackList);//创建此乐器的事件并加到track上
			track.add(makeEvent(176,1,127,0,16));
		}
		//确保16拍有事件,否则beatbox不会重复播放
		track.add(makeEvent(192,9,1,0,15));
		try {
			sequencer.setSequence(sequence);
			//指定无穷的重复次数
			sequencer.setLoopCount(sequencer.LOOP_CONTINUOUSLY);
			//开始播放
			sequencer.start();
			sequencer.setTempoInBPM(120);
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
	//第一个内部类,按钮的监听者
	public class MyStartListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			buildTrackAndStart();
		}
	}
	public class MyStopListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			sequencer.stop();
		}
	}
	public class MyUpTempoListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			float tempoFactor = sequencer.getTempoFactor();
			//节奏因子,预设为1.0
			sequencer.setTempoFactor((float)(tempoFactor * 1.03));
		}
	}
	public class MyDownTempoListencer implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			float tempoFactor = sequencer.getTempoFactor();
			//每次调整为%3
			sequencer.setTempoFactor((float)(tempoFactor * 0.97));
		}
	}
	public void makeTracks(int[] list) {//创建某项乐器所有事件
		for(int i=0;i<16;i++) {
			int key = list[i];
			if(key != 0) {
				//创建NOTE ON和NOTE OFF事件并加入到track上
				track.add(makeEvent(144,9,key,100,i));
				track.add(makeEvent(128,0,key,100,i+1));
			}
		}
	}
	public MidiEvent makeEvent(int comd,int chan,int one,int two,int tick) {
		MidiEvent event = null;
		try {
			ShortMessage a = new ShortMessage();
			a.setMessage(comd,chan,one,two);
			event = new MidiEvent(a,tick);
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		return event;
	}
}
