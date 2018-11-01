
import javax.swing.*;
import javax.swing.border.EtchedBorder;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.SpringLayout;

import java.awt.event.*;
import java.awt.*;

import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;
import javax.swing.UIManager;

public class GUImake implements ActionListener {
  
	public JButton Th_button1;
	public JButton Th_button2;
	public JButton Th_button3;
	public JButton Tr_button1;
	public JButton Tr_button2;
	public static JLabel Th_label3;
	public static JLabel Count_label;
	public JTextField Tr_text1;
	
	public static int flag;
	
	public static  int tm = 0;
	public static  int tr = 100;
	
	
	
	public GUImake() {
		
		SpringLayout layout = new SpringLayout();
	    JPanel p = new JPanel();
	  //フレーム表示
        JFrame f = new JFrame();
        
      //フレームのサイズを指定
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		int sw = screenSize.width/2;
		int sh = screenSize.height/2;
		f.setSize(sw, sh);
		f.setVisible (true);
		//f.setResizable(false);
        f.setLocationRelativeTo(null);
        
        //フレームの表示・非表示を指定
        f.setVisible(true);
      //タイトルをつける  
        f.setTitle("Cheering Controll");
        
      //×を押した時の処理
    	f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	 
    	 p.setSize(sw,sh);
         int p_w =p.getWidth();
         p.setLayout(layout);
    	
          
        //閾値測定メニュー ：パネル 
          JPanel panel1 = new JPanel();
          panel1.setOpaque(false);
          panel1.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
          
          //トレーニング用メニュー：パネル
          JPanel panel2 = new JPanel();
          panel2.setOpaque(false);
          panel2.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
        
          JPanel Count_panel = new JPanel();
          Count_panel.setBackground(Color.WHITE);
          Count_panel.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
          
          int p2_w =panel2.getWidth();
          int p2_h =panel2.getHeight();
          
          
          //閾値測定メニュー：ラベル
          JLabel Titlelabel1 = new JLabel();
          Titlelabel1.setText("閾値測定");
          Titlelabel1.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 25));
          JLabel Th_label1 = new JLabel();
          Th_label1.setText("閾値 : ");
          Th_label1.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 16));
          JLabel Th_label2 = new JLabel();
          Th_label2.setText("[N]");
          Th_label2.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 16));
          //閾値表示用
          Th_label3 = new JLabel();
          Th_label3.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 16));
          
        //トレーニング用メニュー：ラベル  
          JLabel Titlelabel2 = new JLabel();
          Titlelabel2.setText("トレーニング");
          Titlelabel2.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 25));
          JLabel Set_label1 = new JLabel();
          Set_label1.setText("設定");
          Set_label1.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 20));
          JLabel Set_label2 = new JLabel();
          Set_label2.setText("回数 : ");
          Set_label2.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 16));
          JLabel Set_label3 = new JLabel();
          Set_label3.setText("回");
          Set_label3.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 16));
        
        //トレーニングカウント用：ラベル  
          JLabel Count_label1 = new JLabel();
          Count_label1.setText("あと");
          Count_label1.setFont(new Font("ＭＳ ゴシック", Font.PLAIN,20));
          
          JLabel Count_label2 = new JLabel();
          Count_label2.setText("回");
          Count_label2.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 20));
          
          
         //トレーニング用メニュー：テキスト
          Tr_text1 = new JTextField(2);
        //トレーニングカウント表示用：ラベル
          Count_label=new JLabel();
          
        
           
          //閾値用：ボタン
          Th_button1 = new JButton("測定開始");
          Th_button2 = new JButton("測定終了");
          Th_button3 = new JButton("リセット");
        
          //トレーニング用：ボタン
          Tr_button1 = new JButton("スタート");
          Tr_button2 = new JButton("リセット");
          
          //パネル
          layout.putConstraint(SpringLayout.NORTH, panel1, 50, SpringLayout.NORTH, p);
          layout.putConstraint(SpringLayout.SOUTH, panel1, -30, SpringLayout.SOUTH, p);
          layout.putConstraint(SpringLayout.WEST, panel1, 25, SpringLayout.WEST, p);
          layout.putConstraint(SpringLayout.EAST, panel1, p_w/3 , SpringLayout.WEST, p);
          
          layout.putConstraint(SpringLayout.NORTH, panel2, 50, SpringLayout.NORTH, p);
          layout.putConstraint(SpringLayout.SOUTH, panel2, -30, SpringLayout.SOUTH, p);
          layout.putConstraint(SpringLayout.WEST, panel2, 25, SpringLayout.EAST, panel1);
          layout.putConstraint(SpringLayout.EAST, panel2, -25, SpringLayout.EAST, p);
          
          //ラベル
          layout.putConstraint(SpringLayout.SOUTH, Titlelabel1 , -5 , SpringLayout.NORTH, panel1);
          layout.putConstraint(SpringLayout.WEST, Titlelabel1 , 25, SpringLayout.WEST, p);
          
          layout.putConstraint(SpringLayout.SOUTH, Titlelabel2 , -5 , SpringLayout.NORTH, panel2);
          layout.putConstraint(SpringLayout.WEST, Titlelabel2 , 25, SpringLayout.EAST, panel1);
          
        //設定
          layout.putConstraint(SpringLayout.NORTH, Set_label1 , 15 , SpringLayout.NORTH, panel2);
          layout.putConstraint(SpringLayout.WEST, Set_label1 , 20 , SpringLayout.WEST, panel2);
        
          layout.putConstraint(SpringLayout.NORTH, Set_label2 , 30 , SpringLayout.SOUTH, Set_label1);
          layout.putConstraint(SpringLayout.WEST, Set_label2 , 10 , SpringLayout.WEST, Set_label1);
          
          layout.putConstraint(SpringLayout.NORTH, Tr_text1 , 0 , SpringLayout.NORTH,Set_label2 );
          layout.putConstraint(SpringLayout.WEST, Tr_text1 , 5 , SpringLayout.EAST, Set_label2);
          
          layout.putConstraint(SpringLayout.NORTH, Set_label3 , 0 , SpringLayout.NORTH, Set_label2);
          layout.putConstraint(SpringLayout.WEST, Set_label3 , 5 , SpringLayout.EAST, Tr_text1);
          
        //閾値
          layout.putConstraint(SpringLayout.NORTH, Th_label1 , 30 , SpringLayout.NORTH, panel1);
          layout.putConstraint(SpringLayout.WEST, Th_label1 , 25 , SpringLayout.WEST, panel1);
          
          layout.putConstraint(SpringLayout.NORTH, Th_label3 , 0 , SpringLayout.NORTH, Th_label1);
          layout.putConstraint(SpringLayout.WEST, Th_label3 , 5 , SpringLayout.EAST, Th_label1);
          
          layout.putConstraint(SpringLayout.NORTH, Th_label2 , 0 , SpringLayout.NORTH, Th_label1);
          layout.putConstraint(SpringLayout.WEST, Th_label2 , 5 , SpringLayout.EAST, Th_label3);
          
        //カウント
          layout.putConstraint(SpringLayout.NORTH, Count_label1 , 0 , SpringLayout.SOUTH, Set_label1);
          layout.putConstraint(SpringLayout.WEST, Count_label1 , 40 , SpringLayout.EAST, Set_label3);
          
          layout.putConstraint(SpringLayout.NORTH, Count_panel , 5 , SpringLayout.SOUTH, Count_label1);
          layout.putConstraint(SpringLayout.WEST, Count_panel , 0 , SpringLayout.WEST, Count_label1);
          layout.putConstraint(SpringLayout.EAST, Count_panel , -75 , SpringLayout.EAST, panel2);
          layout.putConstraint(SpringLayout.SOUTH, Count_panel , -80 , SpringLayout.SOUTH, panel2);
          
          layout.putConstraint(SpringLayout.NORTH, Count_label , 10 , SpringLayout.NORTH, Count_panel);
          layout.putConstraint(SpringLayout.WEST, Count_label , 10 , SpringLayout.WEST, Count_panel);
          layout.putConstraint(SpringLayout.EAST, Count_label , -10 , SpringLayout.EAST, Count_panel);
          
          layout.putConstraint(SpringLayout.NORTH, Count_label2 , 5 , SpringLayout.SOUTH, Count_panel);
          layout.putConstraint(SpringLayout.EAST, Count_label2 , -15 , SpringLayout.EAST, Count_panel);
          
        //ボタン
          //閾値
          layout.putConstraint(SpringLayout.WEST, Th_button1 , 30 , SpringLayout.WEST, panel1);
          layout.putConstraint(SpringLayout.EAST, Th_button1 , -30 , SpringLayout.EAST, panel1);
          layout.putConstraint(SpringLayout.NORTH, Th_button1 , 75 , SpringLayout.SOUTH, Th_label1);
          
          layout.putConstraint(SpringLayout.WEST, Th_button2 , 30 , SpringLayout.WEST, panel1);
          layout.putConstraint(SpringLayout.EAST, Th_button2 , -30 , SpringLayout.EAST, panel1);
          layout.putConstraint(SpringLayout.NORTH, Th_button2 , 5 , SpringLayout.SOUTH, Th_button1);
          
          layout.putConstraint(SpringLayout.WEST, Th_button3 , 30 , SpringLayout.WEST, panel1);
          layout.putConstraint(SpringLayout.EAST, Th_button3 , -30 , SpringLayout.EAST, panel1);
          layout.putConstraint(SpringLayout.NORTH, Th_button3 , 5 , SpringLayout.SOUTH, Th_button2);
          
          //カウント
          layout.putConstraint(SpringLayout.WEST, Tr_button1 , 10 , SpringLayout.WEST, Set_label2);
          layout.putConstraint(SpringLayout.EAST, Tr_button1 , -5 , SpringLayout.EAST, Set_label3);
          layout.putConstraint(SpringLayout.NORTH, Tr_button1 , 75 , SpringLayout.SOUTH, Set_label2);
          
          layout.putConstraint(SpringLayout.WEST, Tr_button2 , 10 , SpringLayout.WEST, Set_label2);
          layout.putConstraint(SpringLayout.EAST, Tr_button2 , -5 , SpringLayout.EAST, Set_label3);
          layout.putConstraint(SpringLayout.NORTH, Tr_button2 , 5 , SpringLayout.SOUTH, Tr_button1);
          
          p.add(panel1);
          p.add(panel2);
          
          p.add(Titlelabel1);
          p.add(Titlelabel2);

          p.add(Set_label1);
          p.add(Set_label2);
          p.add(Set_label3);
          
          p.add(Th_label1);
          p.add(Th_label2);
          p.add(Th_label3);
          
          p.add(Count_label1);
          p.add(Count_label2);
          p.add(Count_label);
        
          p.add(Tr_text1);
        
          
          p.add(Count_panel);
          
          p.add(Th_button1);
          p.add(Th_button2);
          p.add(Th_button3);
          
          p.add(Tr_button1);
          p.add(Tr_button2);
          
          Th_button1.addActionListener((ActionListener) this);
      	  Th_button2.addActionListener((ActionListener) this);
      	  Th_button3.addActionListener((ActionListener) this);
      	  Tr_button1.addActionListener((ActionListener) this);
      	  Tr_button2.addActionListener((ActionListener) this);
      	
          
          f.getContentPane().add(p, BorderLayout.CENTER);
          
          
	}
	
	public void actionPerformed(ActionEvent event){
        // ユーザーの操作対象を判断
    	//閾値測定ボタン設定
        if(event.getSource() == Th_button1) {
        	 tm = 1;
        }
        
        if(event.getSource() == Th_button2) {
       	 tm = 2; 
       	/* if(Cheering_controlImpl.thresholdString!=null){
       	 Th_label3.setText(Cheering_controlImpl.thresholdString);
       	 }*/
       }
        
        if(event.getSource() == Th_button3) {
       	 tm = 3; 
       /*	if(Cheering_controlImpl.thresholdString!=null){
          	 Th_label3.setText(Cheering_controlImpl.thresholdString);
          	 }*/
       	
       	
       }
	
      //トレーニングボタン設定
        if(event.getSource() == Tr_button1) {
        	String tr1 = Tr_text1.getText();
        	tr=Integer.parseInt(tr1);
        	Count_label.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 110));
        	Count_label.setText(tr1);
        	flag=1;
        	
        }//Tr_button1
        
        
        if(event.getSource() == Tr_button2) {
        	Count_label.setText("00");
        	Count_label.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 110));
        	Count_label.setForeground(Color.BLACK);
        	flag=0;
        	tr=0;
       }//Tr_button2
        
        
	}//actionPerformed
	
	

}//class

class CountSwingWorker extends SwingWorker<Object,Object> {
	public int remaining;
	static String countString;
	@Override
	protected Object doInBackground() throws Exception {
		
		//カウント計算
		if(GUImake.flag==1){
		    remaining=GUImake.tr-Cheering_controlImpl.count;
			countString= String.valueOf(remaining);
		}
		if(GUImake.flag==0){
			remaining=0;
			Cheering_controlImpl.count=0;
		}
	return null;
	}

	protected void done() {     
		if(remaining>3 && GUImake.flag == 1){
			GUImake.Count_label.setForeground(Color.BLACK);
			GUImake.Count_label.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 110));
			GUImake.Count_label.setText(countString);
		  }
		if(remaining>3&& 10>remaining && GUImake.flag == 1){
			GUImake.Count_label.setForeground(Color.BLACK);
			GUImake.Count_label.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 110));
			GUImake.Count_label.setText("0"+countString);
		  }
		if(remaining<=3 && GUImake.flag == 1){
			GUImake.Count_label.setForeground(Color.RED);
			GUImake.Count_label.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 110));
			GUImake.Count_label.setText("0"+countString);
			
		  }
		if(remaining <=0 && GUImake.flag == 1){
			GUImake.Count_label.setFont(new Font("ＭＳ ゴシック", Font.PLAIN, 40));
			GUImake.Count_label.setForeground(Color.RED);
			GUImake.Count_label.setText("終了");
		}
	
}
}

class ThresholdSwingWorker extends SwingWorker<Object,Object> {
	public int remaining;
	static String countString;
	@Override
	protected Object doInBackground() throws Exception {
			
		
	return null;
	}

	protected void done() {     
		if(GUImake.tm==2||GUImake.tm==3){
	       	 GUImake.Th_label3.setText(Cheering_controlImpl.thresholdString);
	       	 }
		
}
}