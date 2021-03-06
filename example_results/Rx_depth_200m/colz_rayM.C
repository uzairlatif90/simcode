
void make_chain_from_dir(TString dirname, TChain * chain, TString starts_with, TString ends_with);

void colz_rayM(){

  TString dirname;
  TString starts_with;
  TString ends_with; 
  TChain *cchTreeR=new TChain("chTreeR");
  dirname="./";
  starts_with="z200";
  ends_with="RKresults.root"; 
  make_chain_from_dir(dirname,cchTreeR,starts_with,ends_with);
  cout<<"Filled chTreeR chain"<<endl;

  const  Int_t nxyzoutr=3;
  const  Int_t nxzoutr=2;
  Int_t nxyzr;
  Int_t nxzr;
  Int_t isolbrr;
  Double_t rTxr[nxyzoutr];  
  Double_t rRxr[nxyzoutr];
  Double_t xzTxr[nxzoutr]; 
  Double_t xzRxr[nxzoutr];
  Double_t TransitTimer;
  Double_t AttFacr;
  Double_t L_angr;
  Double_t R_angr;
  Double_t I_angr;
  Double_t I_corr[nxzoutr];
  Char_t WasSurfaceHitr;

  cchTreeR->SetBranchAddress("nxyz",&nxyzr);
  cchTreeR->SetBranchAddress("nxz",&nxzr);
  cchTreeR->SetBranchAddress("isolbr",&isolbrr);
  cchTreeR->SetBranchAddress("rTx",rTxr);
  cchTreeR->SetBranchAddress("rRx",rRxr);
  cchTreeR->SetBranchAddress("xzTx",xzTxr);
  cchTreeR->SetBranchAddress("xzRx",xzRxr);
  cchTreeR->SetBranchAddress("TransitTime",&TransitTimer);
  cchTreeR->SetBranchAddress("AttFac",&AttFacr);
  cchTreeR->SetBranchAddress("L_ang",&L_angr);
  cchTreeR->SetBranchAddress("R_ang",&R_angr);
  cchTreeR->SetBranchAddress("I_ang",&I_angr);
  cchTreeR->SetBranchAddress("I_cor",I_corr);
  cchTreeR->SetBranchAddress("WasSurfaceHit",&WasSurfaceHitr);
  
  Int_t Mentries=cchTreeR->GetEntries();
  
  TH2D *hist2dReD=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dRaD=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dD=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dRe=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dRa=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dReD_ang=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dRaD_ang=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dD_ang=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dRe_ang=new TH2D("","",100,0,1000,100,-1000,0);
  TH2D *hist2dRa_ang=new TH2D("","",100,0,1000,100,-1000,0);
  
  cout<<"The total entries are "<<Mentries<<endl;

  gStyle->SetPalette(kCMYK);
  gStyle->SetPalette(kBird);

  Double_t rTxM[3][nxyzoutr];  
  Double_t rRxM[3][nxyzoutr];
  Double_t xzTxM[3][nxzoutr]; 
  Double_t xzRxM[3][nxzoutr];
  Double_t TransitTimeM[3];
  Double_t AttFacM[3];
  Double_t L_angM[3];
  Double_t R_angM[3];
  Char_t WasSurfaceHitM[3];
  
  Int_t iso=0;
  for(Int_t ievtr=0;ievtr<Mentries;ievtr++){  
    cchTreeR->GetEntry(ievtr);
    
    for(Int_t ixyz=0;ixyz<nxyzoutr;ixyz++){
      rTxM[isolbrr][ixyz]=rTxr[ixyz];  
      rRxM[isolbrr][ixyz]=rRxr[ixyz];
    }
    for(Int_t ixz=0;ixz<nxzoutr;ixz++){
      xzTxM[isolbrr][ixz]=xzTxr[ixz]; 
      xzRxM[isolbrr][ixz]=xzRxr[ixz];
    }
    TransitTimeM[isolbrr]=TransitTimer;
    AttFacM[isolbrr]=AttFacr;
    L_angM[isolbrr]=L_angr;
    R_angM[isolbrr]=R_angr;
    WasSurfaceHitM[isolbrr]=WasSurfaceHitr;
    
    iso++;
    
    if(iso==3){

      if(R_angM[1]>-1 && R_angM[0]>-1 && WasSurfaceHitM[1]==true &&  WasSurfaceHitM[0]==false){
      	hist2dReD->Fill(xzTxM[0][0],xzTxM[0][1],fabs(TransitTimeM[1]-TransitTimeM[0])*pow(10,9));
	// if((TransitTimeM[1]-TransitTimeM[0])*pow(10,9)<0){
	//   cout<<"inside D-Re loop "<<xzTxM[0][0]<<" "<<xzTxM[0][1]<<" "<<(TransitTimeM[1]-TransitTimeM[0])*pow(10,9)<<endl;
	// }
      }

      if(R_angM[2]>-1 && R_angM[0]>-1 && WasSurfaceHitM[2]==false &&  WasSurfaceHitM[0]==false){
      	hist2dRaD->Fill(xzTxM[0][0],xzTxM[0][1],(TransitTimeM[2]-TransitTimeM[0])*(pow(10,9)));
      }

      if(R_angM[0]>-1 && WasSurfaceHitM[0]==false){
      	hist2dD->Fill(xzTxM[0][0],xzTxM[0][1],TransitTimeM[0]*pow(10,9));
	hist2dD_ang->Fill(xzTxM[0][0],xzTxM[0][1],L_angM[0]);
      }
      
      if(R_angM[1]>-1 && WasSurfaceHitM[1]==true){
      	hist2dRe->Fill(xzTxM[1][0],xzTxM[1][1],TransitTimeM[1]*pow(10,9));
	hist2dRe_ang->Fill(xzTxM[0][0],xzTxM[0][1],L_angM[1]);
      }
      
      if(R_angM[2]>-1 && WasSurfaceHitM[2]==false){
      	hist2dRa->Fill(xzTxM[2][0],xzTxM[2][1],TransitTimeM[2]*pow(10,9));
	hist2dRa_ang->Fill(xzTxM[0][0],xzTxM[0][1],L_angM[2]);
      }
      
      if(R_angM[1]>-1 && R_angM[0]>-1 && WasSurfaceHitM[1]==true &&  WasSurfaceHitM[0]==false){
      	//if(fabs(L_angM[1]-L_angM[0])<1){
     	  hist2dReD_ang->Fill(xzTxM[0][0],xzTxM[0][1],L_angM[0]-L_angM[1]);
	  //}
      }
      
      if(R_angM[2]>-1 && R_angM[0]>-1 && WasSurfaceHitM[2]==false &&  WasSurfaceHitM[0]==false){
	//      	if((L_angM[2]-L_angM[0])<5){
      	  hist2dRaD_ang->Fill(xzTxM[0][0],xzTxM[0][1],L_angM[0]-L_angM[2]);	
	  //}
      } 
    }
      
    if(iso==3){
      iso=0;
    }
    
  }//ievt loop

  gStyle->SetPadLeftMargin(0.07);
  
  TCanvas *c8=new TCanvas("c8","c8",1800,1100);
  c8->cd();
  hist2dReD->SetStats(0);
  hist2dReD->Draw("colz");
  hist2dReD->SetTitle("Time of Reflected Ray-Direct Ray , Receiver at z=-200 m, x=1000 m, Step size=50;X (m);Z (m); Time (ns)");
  hist2dReD->GetZaxis()->SetLabelSize(0.03);
  hist2dReD->GetZaxis()->SetTitleOffset(0.7);
  
  TCanvas *c9=new TCanvas("c9","c9",1800,1100);
  c9->cd();
  hist2dRaD->SetStats(0);
  hist2dRaD->Draw("colz");
  hist2dRaD->SetTitle("Time of Refracted ray-Direct Ray , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m) ;Z (m); Time (ns)");
  hist2dRaD->GetZaxis()->SetLabelSize(0.03);
  hist2dRaD->GetZaxis()->SetTitleOffset(0.7);
  
  TCanvas *c10=new TCanvas("c10","c10",1800,1100);
  c10->cd();
  hist2dD->SetStats(0);
  hist2dD->Draw("colz");
  hist2dD->SetTitle("Time of Direct Ray , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m) ;Z (m); Time (ns)");
  hist2dD->GetZaxis()->SetLabelSize(0.03);
  hist2dD->GetZaxis()->SetTitleOffset(0.7);
  
  TCanvas *c11=new TCanvas("c11","c11",1800,1100);
  c11->cd();
  hist2dRe->SetStats(0);
  hist2dRe->Draw("colz");
  hist2dRe->SetTitle("Time of Reflected Ray , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m) ;Z (m); Time (ns)");
  hist2dRe->GetZaxis()->SetLabelSize(0.03);
  hist2dRe->GetZaxis()->SetTitleOffset(0.7);

  TCanvas *c12=new TCanvas("c12","c12",1800,1100);
  c12->cd();
  hist2dRa->SetStats(0);
  hist2dRa->Draw("colz");
  hist2dRa->SetTitle("Time of Refracted ray , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m) ;Z (m); Time (ns)");
  hist2dRa->GetZaxis()->SetLabelSize(0.03);
  hist2dRa->GetZaxis()->SetTitleOffset(0.7);
  
  TCanvas *c13=new TCanvas("c13","c13",1800,1100);
  c13->cd();
  hist2dReD_ang->SetStats(0);
  hist2dReD_ang->Draw("colz");
  hist2dReD_ang->SetTitle("Launch angle difference of D-Re #circ , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m);Z (m); Angle diff. (deg)");
  hist2dReD_ang->GetZaxis()->SetLabelSize(0.03);
  hist2dReD_ang->GetZaxis()->SetTitleOffset(0.7);
  
  TCanvas *c14=new TCanvas("c14","c14",1800,1100);
  c14->cd();
  hist2dRaD_ang->SetStats(0);
  hist2dRaD_ang->Draw("colz");
  hist2dRaD_ang->SetTitle("Launch angle difference of D-Ra #circ , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m);Z (m);Angle diff. (deg)");
  hist2dRaD_ang->GetZaxis()->SetLabelSize(0.03);
  hist2dRaD_ang->GetZaxis()->SetTitleOffset(0.7);

  TCanvas *c15=new TCanvas("c15","c15",1800,1100);
  c15->cd();
  hist2dD_ang->SetStats(0);
  hist2dD_ang->Draw("colz");
  hist2dD_ang->SetTitle("Launch angle of Direct Ray , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m) ;Z (m); Time (ns)");
  hist2dD_ang->GetZaxis()->SetLabelSize(0.03);
  hist2dD_ang->GetZaxis()->SetTitleOffset(0.7);
  
  TCanvas *c16=new TCanvas("c16","c16",1800,1100);
  c16->cd();
  hist2dRe_ang->SetStats(0);
  hist2dRe_ang->Draw("colz");
  hist2dRe_ang->SetTitle("Launch angle of Reflected Ray , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m) ;Z (m); Time (ns)");
  hist2dRe_ang->GetZaxis()->SetLabelSize(0.03);
  hist2dRe_ang->GetZaxis()->SetTitleOffset(0.7);

  TCanvas *c17=new TCanvas("c17","c17",1800,1100);
  c17->cd();
  hist2dRa_ang->SetStats(0);
  hist2dRa_ang->Draw("colz");
  hist2dRa_ang->SetTitle("Launch angle of Refracted ray , Receiver at z=-200 m, x=1000 m, Step size=50 m;X (m) ;Z (m); Time (ns)");
  hist2dRa_ang->GetZaxis()->SetLabelSize(0.03);
  hist2dRa_ang->GetZaxis()->SetTitleOffset(0.7);
  
  c8->SaveAs("Time_ReD_z200.png");
  c9->SaveAs("Time_RaD_z200.png");
  c10->SaveAs("Time_D_z200.png");
  c11->SaveAs("Time_Re_z200.png");
  c12->SaveAs("Time_Ra_z200.png");
  c13->SaveAs("Angle_ReD_z200.png");
  c14->SaveAs("Angle_RaD_z200.png"); 
  c15->SaveAs("Angle_D_z200.png");
  c16->SaveAs("Angle_Re_z200.png");
  c17->SaveAs("Angle_Ra_z200.png");
  
}

void make_chain_from_dir(TString dirname, TChain * chain, TString starts_with, TString ends_with){
  //TChain * chain = new TChain(chainname);
  //go through directory, add all files to the chain.                    
  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();
  files->Sort();
  if(files){
    TSystemFile *file;
    TString fname;  
    TString ext = "root";
    TIter next(files);
    Int_t n=1;
    while((file=(TSystemFile*)next())){
      fname = file->GetName();
      
      if(!file->IsDirectory() && fname.BeginsWith(starts_with) && fname.EndsWith(ends_with) && n<9){
	
       	// for(int i=1;i<9;i++){
        //add the file to the chain
	//  dirname+=i;
	//  dirname+="/";
	
	TString fname1=starts_with;  
      	//fname1+=n*25;
	fname1+=ends_with;                                      
        chain->Add(dirname+fname1);
	cout<<fname1<<endl;
	n++;        
	//      return chain;     
	//	 }                                       
      }
    }
  }
}

