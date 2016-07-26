/*-------------------------------------------------------------------*/
/* ITS60304– Assignment #1 */
/* C Programming */
/* Student Name: <Lim Cheng Qing> <Mohammad Ramzan Ashraf> */
/* Student ID: <0324306> <0323724> */
/*-------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>

		
	struct gstproduct	//struct for gst purchase function
	{
		char gstcode[5000][5];
		char gstname[5000][50];
		unsigned int gstquantity[5000];
		float gstprice[5000];
	};
	struct ngstproduct	//struct for ngst purchase function 
	{
		char ngstcode[5000][5];
		char ngstname[5000][20];
		unsigned int ngstquantity[5000];
		float ngstprice[5000];
	};
	struct productchanges	//Struct for edit function
	{
		char ccode[5000][5];
		char cname[5000][20];
		unsigned int cquantity[5000];
		float cprice[5000];
	};
	struct purchase		//Struct for print receipt function
	{
		char receipt[4];
		char rname[5000][20];
		float rprice[5000];
		float rtotal[5000];
		float ramount;
		unsigned int rquantity[5000];
	};
	struct editvariable // Struct for edit function
	{
			char editcode[10], editfield[10], newname[50];
			float editprice;
			int editquantity;
		
	};
	struct additem // Struct for add item function
	{
		char newid[5],newname[50];
		float newprice;
		int newquantity;
	};
	
	struct deleteitem // Struct for delete item function
	{
		char deleteid[5];
		int deleteinput;
	};
	void printtable();  // Print operation table
int main (void)
{
	struct gstproduct gstproduct_1;
	struct ngstproduct ngstproduct_1;
	struct productchanges productchanges_1;
	struct purchase purchase_1;
	struct editvariable editvariable_1;
	struct additem additem_1;
	struct deleteitem deleteitem_1;
	char code[5];
	char quit [10];
	unsigned int quantity;
	int i=0,k=0,x=0,c=0;   // initializer
	char a[20];
	int sale=0;
	char input;
	float gsttotal=0, ngsttotal=0, totalgst;
	clock_t latesttime;
	FILE *edit = fopen("edit.txt", "a+");
	FILE *gst = fopen("gst.txt", "a+");
	FILE *writegst;
	FILE *writengst;
	FILE *ngst = fopen ("ngst.txt", "a+");
	FILE *record = fopen("purchase.txt", "a+");
	latesttime = time(NULL);
	if ((gst == NULL ) || (ngst == NULL) || (record == NULL) || (edit == NULL))
	{
		printf ("File doesn't exist please try again\n");
		exit(101);
	}
	else 
	{
		while(!feof(edit))
		{
			fscanf(edit, "%5c;%[a-zA-z ];%f;%d\n", productchanges_1.ccode[i], productchanges_1.cname[i], &productchanges_1.cprice[i], &productchanges_1.cquantity[i]);
			i++;
		}
		while (!feof(gst))
		{		
			fscanf(gst, "%5c;%[a-zA-z ];%f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], &gstproduct_1.gstprice[i], &gstproduct_1.gstquantity[i]);
			i++;
		}
		while(!feof(ngst))
		{
			fscanf(ngst, "%5c;%[a-zA-z ];%f;%d\n", ngstproduct_1.ngstcode[i], ngstproduct_1.ngstname[i], &ngstproduct_1.ngstprice[i], &ngstproduct_1.ngstquantity[i]);			
			i++;
		}
	}	// READ/Scan all letters into variables
		LOOP:		// goto LOOP declaration
		printtable(); 
		printf("\nEnter operation number\n");
		FINALLOOP:	// goto loop declaration
		if ((input = getchar()) == '\n')     // kill \n from getchar
		{
			goto FINALLOOP;
		}

		switch(input)
		{
			case '1' :
			LOOP2:
			printf("Enter item code. -1 to exit\n");
			scanf("%s", code);
			if (strncmp(code, "-1",5)==0)
			{
				printf("Would you like a receipt\n");
				scanf("%s", purchase_1.receipt);
				if ((strncmp(purchase_1.receipt, "yes",4)== 0) || (strncmp(purchase_1.receipt, "Yes",4)==0) || 
				(strncmp(purchase_1.receipt, "yEs",4)==0)	|| (strncmp(purchase_1.receipt, "yeS",4)==0) || 
				(strncmp(purchase_1.receipt, "YEs",4)==0) || (strncmp(purchase_1.receipt, "YES",4)==0) ||
				(strncmp(purchase_1.receipt, "yES",4)==0))
				{
					rewind (record);
					while (!feof(record))
					{			
						fscanf(record, "%[a-zA-Z ]\t%f\t%d\t%f\n", purchase_1.rname[k], &purchase_1.rprice[k], &purchase_1.rquantity[k], &purchase_1.rtotal[k]);
						printf("%-10.20s\t%10.2f\t%d\t\t\t%.2f\n", purchase_1.rname[k], purchase_1.rprice[k], purchase_1.rquantity[k], purchase_1.rtotal[k]);
						purchase_1.ramount += purchase_1.rtotal[k];
						k++;
					}	
					printf("______________________________________________________________\n");
					printf("\t\t\t\t\t\t\t%.2f", purchase_1.ramount);
					printf("\nTime: ");
					printf(ctime(&latesttime));
					printf("\n==============================================================\n\n\n");
					goto LOOP;		//GO back to operation table
				}
			
				else if ((strncmp(purchase_1.receipt, "no",4)== 0) || (strncmp(purchase_1.receipt, "NO",4)==0) || 
				(strncmp(purchase_1.receipt, "No",4)==0)	|| (strncmp(purchase_1.receipt, "nO",4)==0))
				{
					printf("No receipt.\n");
					goto LOOP;		// GO back to operation table
				}
			}	
			printf("Enter number of quantity\n");
			scanf("%d", &quantity);
			if (quantity == -1)
			{
				printf("Would you like a receipt\n");
				scanf("%s", purchase_1.receipt);
				if ((strncmp(purchase_1.receipt, "yes",4)== 0) || (strncmp(purchase_1.receipt, "Yes",4)==0) || 
				(strncmp(purchase_1.receipt, "yEs",4)==0)	|| (strncmp(purchase_1.receipt, "yeS",4)==0) || 
				(strncmp(purchase_1.receipt, "YEs",4)==0) || (strncmp(purchase_1.receipt, "YES",4)==0) )
				{
				rewind(record);
					while (!feof(record))
					{			
						fscanf(record, "%[a-zA-Z ]\t%f\t%d\t%f\n", purchase_1.rname[k], &purchase_1.rprice[k], &purchase_1.rquantity[k], &purchase_1.rtotal[k]);
						//%-10.20s\t%10.2f\t%d\t%.2f
						//%-10.20s\t%8.2f\t%d\t\t\t%.2f\n
						printf("%-10.20s\t%10.2f\t%d\t\t\t%.2f\n", purchase_1.rname[k], purchase_1.rprice[k], purchase_1.rquantity[k], purchase_1.rtotal[k]);
						purchase_1.ramount += purchase_1.rtotal[k];
						k++;
					}	
					printf("______________________________________________________________\n");
					printf("\t\t\t\t\t\t\t%.2f", purchase_1.ramount);
					printf("\nTime: ");
					printf(ctime(&latesttime));				// print latest time 
					printf("\n==============================================================\n\n\n");
					goto LOOP;		// Go to operation table
				}
			
				else if ((strncmp(purchase_1.receipt, "no",4)== 0) || (strncmp(purchase_1.receipt, "NO",4)==0) || 
				(strncmp(purchase_1.receipt, "No",4)==0)	|| (strncmp(purchase_1.receipt, "nO",4)==0))
				{
					printf("No receipt.\n");
					goto LOOP; 		// goto operation table
				}
			}
			for (i=0; i<500; i++)
			{
				if (strncmp(code, gstproduct_1.gstcode[i], 5)== 0 || strncmp(code, ngstproduct_1.ngstcode[i],5) ==0) 
				{
					if (strncmp(code, gstproduct_1.gstcode[i], 5)== 0 && gstproduct_1.gstquantity[i]> quantity)
					{
						gsttotal += (gstproduct_1.gstprice[i]*quantity*1.06);
						printf("Product is %s\n", gstproduct_1.gstname[i]);
						printf("Price is %.2f\n", gstproduct_1.gstprice[i]);
						printf("Subtotal is %.2f\n", gsttotal);
						totalgst += gsttotal - (gstproduct_1.gstprice[i]*quantity);
						fprintf(record,"%s\t%.2f\t%d\t%.2f\n",gstproduct_1.gstname[i], gstproduct_1.gstprice[i], quantity, gsttotal);
						sale++;
						goto LOOP2; 
					}
					else if (strncmp(code, ngstproduct_1.ngstcode[i],5) ==0 && ngstproduct_1.ngstquantity[i]>quantity)
					{
						ngsttotal += (ngstproduct_1.ngstprice[i]*quantity);
						printf("Product is %s\n", ngstproduct_1.ngstname[i]);
						printf("Price is %.2f\n", ngstproduct_1.ngstprice[i]);
						printf("Subtotal is %.2f\n", ngsttotal);
						fprintf(record, "%s\t%.2f\t%d\t%.2f\n", ngstproduct_1.ngstname[i],ngstproduct_1.ngstprice[i], quantity, ngsttotal);
						sale++;
						goto LOOP2;
					}			
				}
			}
					while (strncmp(quit, "-1",5)!= 0)
					{
						printf("Invalid Item. Press -1 to try again\n");
						scanf("%s", quit);
						quantity = 0;
						if (strncmp(quit, "-1",5)== 0)
						{
							printf("Exit success\n");
							goto LOOP2;
					    }						
						else
							printf("Please try again\n");
					}	
						goto LOOP2;
							
			break;
			case '2':
			printf("This option allow user to edit item.\n");
			rewind(gst);
			rewind(ngst);
			rewind(edit);
			while (!feof(gst))
				{				
					i = 0;
					fscanf(gst, "%5c;%[a-zA-z ];%f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], &gstproduct_1.gstprice[i], &gstproduct_1.gstquantity[i]);	
					i++;
				}
			while(!feof(ngst))
				{
					i=0;
					fscanf(ngst, "%5c;%[a-zA-z ];%f;%d\n", ngstproduct_1.ngstcode[i], ngstproduct_1.ngstname[i], &ngstproduct_1.ngstprice[i], &ngstproduct_1.ngstquantity[i]);
					i++;
				}	
			while(!feof(edit))
				{
					i=0;
					fscanf(edit, "%5c;%[a-zA-z ];%f;%d\n", productchanges_1.ccode[i], productchanges_1.cname[i], &productchanges_1.cprice[i], &productchanges_1.cquantity[i]);
					i++;
				}
				LOOP3:
				printf("EDIT ITEM NAME = NAME\nITEM PRICE = PRICE\nITEM QUANTITY = QUANTITY\n");
				printf("Enter item code to be edited. -1 to exit\n");
				scanf("%s", editvariable_1.editcode);
				if (strncmp(editvariable_1.editcode, "-1", 2)==0)
				{
					goto LOOP;
				}
				printf("Enter field to be edit. -1 to exit.\n");
				scanf("%s", editvariable_1.editfield);
				if (strncmp(editvariable_1.editfield, "-1", 2)==0)
				{
					goto LOOP;
				}
				for (i=0; i<500; i++)
				{
					if (strncmp(editvariable_1.editcode, gstproduct_1.gstcode[i], 5)== 0 ) 
						{
							if (strncmp(editvariable_1.editfield, "NAME", 4)== 0)
							{
								printf("Please enter new name for %.5s\n", gstproduct_1.gstcode[i]);
								scanf("%s", editvariable_1.newname);
								strncpy(gstproduct_1.gstname[i], editvariable_1.newname, 10);
								fflush(edit);
								fprintf(edit, "%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], gstproduct_1.gstprice[i], gstproduct_1.gstquantity[i]);	
								fflush(edit);
								printf("Success\n");
								remove("gst.txt");									//Delete and rewrite NAME GST Changes
								writegst = fopen("gst.txt","w+");
								rewind(writegst);
								fflush(writegst);
								for (i=1; i<2000; i++)
								{
									if (gstproduct_1.gstprice[i] ==  0)
									{
										gstproduct_1.gstcode[i][0] = '\0';
										gstproduct_1.gstname[i][0] = '\0';				//Nullify all value
										gstproduct_1.gstprice[i] = '\0';
										gstproduct_1.gstquantity[i] = '\0';
										
									}
									else 
									{	
										fprintf(writegst,"%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], gstproduct_1.gstprice[i], gstproduct_1.gstquantity[i]);
									}
								}
								fflush(writegst);
								fclose(writegst); 
								goto LOOP3; 			// Go to option 3
							}
							if (strncmp(editvariable_1.editfield, "PRICE", 5)==0)
							{
								printf("Please enter new price for %.5s\n", gstproduct_1.gstcode[i]);
								scanf("%f", &editvariable_1.editprice);
								gstproduct_1.gstprice[i] = editvariable_1.editprice;
								fflush(edit);
								fprintf(edit, "%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], gstproduct_1.gstprice[i], gstproduct_1.gstquantity[i]);	
								fflush(edit);
								remove("gst.txt");
								writegst = fopen("gst.txt","w+");						// Delete and rewrite GST PRICE changes
								rewind(writegst);
								fflush(writegst);
								for (i=1; i<2000; i++)
								{
									if (gstproduct_1.gstprice[i] ==  0)
									{
										gstproduct_1.gstcode[i][0] = '\0';
										gstproduct_1.gstname[i][0] = '\0';
										gstproduct_1.gstprice[i] = '\0';
										gstproduct_1.gstquantity[i] = '\0';
									}
									else 
									{	
										fprintf(writegst,"%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], gstproduct_1.gstprice[i], gstproduct_1.gstquantity[i]);
									}
								}
								fflush(writegst);
								fclose(writegst); 
								goto LOOP3;				// go to Option 3
							}
							if (strncmp(editvariable_1.editfield, "QUANTITY", 8)==0)
							{
								printf("Please enter new quantity for %.5s\n", gstproduct_1.gstcode[i]);
								scanf("%d", &editvariable_1.editquantity);
								gstproduct_1.gstquantity[i] = editvariable_1.editquantity;
								fflush(edit);
								fprintf(edit, "%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], gstproduct_1.gstprice[i], gstproduct_1.gstquantity[i]);	
								fflush(edit);
								remove("gst.txt");									
								writegst = fopen("gst.txt","w+");						//Delete and rewrite QUANTITY GST FILE
								rewind(writegst);
								fflush(writegst);								
								for (i=1; i<2000; i++)
								{
									if (gstproduct_1.gstprice[i] ==  0)
									{
										gstproduct_1.gstcode[i][0] = '\0';
										gstproduct_1.gstname[i][0] = '\0';						// Nullify all value
										gstproduct_1.gstprice[i] = '\0';
										gstproduct_1.gstquantity[i] = '\0';
										
									}
									else 
									{	
										fprintf(writegst,"%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], gstproduct_1.gstprice[i], gstproduct_1.gstquantity[i]);
									}
								}
								fflush(writegst);
								fclose(writegst);
								goto LOOP3;				//Go to option 3
							} 
						}	
						else if (strncmp(editvariable_1.editcode, ngstproduct_1.ngstcode[i], 5) ==0) 
							{
								if (strncmp(editvariable_1.editfield, "NAME",4)==0)
								{
									printf("Please enter new name for %.5s\n", ngstproduct_1.ngstcode[i]);
									scanf("%s", editvariable_1.newname);
									strncpy(ngstproduct_1.ngstname[i], editvariable_1.newname, 10);
									fflush(edit);
									fprintf(edit, "%.5s;%s;%.2f;%d\n", ngstproduct_1.ngstcode[i], ngstproduct_1.ngstname[i], ngstproduct_1.ngstprice[i], ngstproduct_1.ngstquantity[i]);	
									fflush(edit);
									remove("ngst.txt");											//delete and rewrite NAME
									writengst = fopen("ngst.txt","w+");
									rewind(writengst);
									fflush(writengst);
									for (i=1; i<2000; i++)
									{
										if (gstproduct_1.gstprice[i] ==  0)
										{
											ngstproduct_1.ngstcode[i][0] = '\0';			// Nullify all value 
											ngstproduct_1.ngstname[i][0] = '\0';
											ngstproduct_1.ngstprice[i] = '\0';
											ngstproduct_1.ngstquantity[i] = '\0';	
										}
										else 
										{	
											fprintf(writegst,"%.5s;%s;%.2f;%d\n", ngstproduct_1.ngstcode[i], ngstproduct_1.ngstname[i], ngstproduct_1.ngstprice[i], ngstproduct_1.ngstquantity[i]);
										}	
										}
										fflush(writengst);
										fclose(writengst);
										goto LOOP3;						// GO to option 3
								}
								if (strncmp(editvariable_1.editfield, "PRICE",5)==0)
								{
									printf("Please enter new price for %.5s\n", ngstproduct_1.ngstcode[i]);
									scanf("%f", &editvariable_1.editprice);
									ngstproduct_1.ngstprice[i] = editvariable_1.editprice;
									fflush(edit);
									fprintf(edit, "%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], gstproduct_1.gstprice[i], gstproduct_1.gstquantity[i]);	
									fflush(edit);
									remove("ngst.txt");								//Delete and rewrite NGST PRICE Changes
									writengst = fopen("ngst.txt","w+");
									rewind(writengst);
									fflush(writengst);
									for (i=1; i<2000; i++)
									{
										if (ngstproduct_1.ngstprice[i] != 0)
										{
											fprintf(writengst, "%.5s;%s;%.2f;%d\n", ngstproduct_1.ngstcode[i], ngstproduct_1.ngstname[i], ngstproduct_1.ngstprice[i], ngstproduct_1.ngstquantity[i]);
										}
									}
									fflush(writengst);
									fclose(writengst);
									goto LOOP3;
								}
								if(strncmp(editvariable_1.editfield, "QUANTITY", 8)==0)
								{
									printf("Please enter new quantity for %.5s\n", ngstproduct_1.ngstcode[i]);
									scanf("%d", &editvariable_1.editquantity);
									ngstproduct_1.ngstquantity[i] = editvariable_1.editquantity;
									fflush(edit);
									fprintf(edit, "%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], gstproduct_1.gstprice[i], gstproduct_1.gstquantity[i]);	
									fflush(edit);
									remove("ngst.txt");								//Delete and rewrite quantity changes
									writengst = fopen("ngst.txt","w+");
									rewind(writengst);
									fflush(writengst);
									for (i=1; i<2000; i++)
									{
										if (ngstproduct_1.ngstprice[i] != 0)
										{
											fprintf(writengst, "%.5s;%s;%.2f;%d\n", ngstproduct_1.ngstcode[i], ngstproduct_1.ngstname[i], ngstproduct_1.ngstprice[i], ngstproduct_1.ngstquantity[i]);
										}
									}
									fflush(writengst);
									fclose(writengst);
									goto LOOP3;
								}
							}
				}
						printf("Invalid behavior please try again\n");
						goto LOOP;
						break;
			case '3':
			rewind(gst);
			rewind(ngst);
			rewind(edit);
			while (!feof(gst))
				{
					i = 0;
					fscanf(gst, "%5c;%[a-zA-z ];%f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], &gstproduct_1.gstprice[i], &gstproduct_1.gstquantity[i]);	
					i++;
				}
			while(!feof(ngst))
				{
					i= 0;
					fscanf(ngst, "%5c;%[a-zA-z ];%f;%d\n", ngstproduct_1.ngstcode[i], ngstproduct_1.ngstname[i], &ngstproduct_1.ngstprice[i], &ngstproduct_1.ngstquantity[i]);
					i++;
				}				
			while(!feof(edit))
				{
					i= 0;
					fscanf(edit, "%5c;%[a-zA-z ];%f;%d\n", productchanges_1.ccode[i], productchanges_1.cname[i], &productchanges_1.cprice[i], &productchanges_1.cquantity[i]);
					i++;
				}
			printf("This option allow user to add item.\n");
			printf("GST for gst item. NGST for ngst item.\n");
			printf("Enter GST OR NGST.\n");
			scanf("%s", editvariable_1.editcode);
			if (strncmp(editvariable_1.editcode, "GST",3)== 0)
			{
				printf("Enter item code.\n");
				scanf("%s", additem_1.newid);
				for (i=0; i <5000; i++)
				{
					if (strncmp(additem_1.newid, gstproduct_1.gstcode[i], 5)==0 || strncmp(additem_1.newid, ngstproduct_1.ngstcode[i], 5)==0)
					{
						printf("ID existed! Program exit.\n");
						goto LOOP;										// Counter the existance of same PRODUCT IC
					}
				}
				printf("Enter item name.\n");
				scanf("%s", additem_1.newname);
				for (i=1; i <5000; i++)
				{
					if (strncmp(additem_1.newname, gstproduct_1.gstname[i], 5)==0 || strncmp(additem_1.newname, ngstproduct_1.ngstname[i], 5)==0)
					{
						printf("Product existed! Program exit.\n");
						goto LOOP;										//Counter to ensure SAME PRODUCT NOT EXIST
					}
				}
				printf("Enter item price.\n");
				scanf("%f", &additem_1.newprice);
				if (additem_1.newprice == 0 )
				{
					printf("Item price can't be 0.\n");
					goto LOOP;
				}
				printf("Enter item quantity.\n");
				scanf("%d", &additem_1.newquantity);
				//fflush(gst);
				fprintf(gst, "\n%.5s;%s;%.2f;%d\n", additem_1.newid, additem_1.newname, additem_1.newprice, additem_1.newquantity);
				fflush(gst);							//Add item by writting into file
			}
			else if (strncmp(editvariable_1.editcode, "NGST",4)== 0)
			{
				printf("Enter item code.\n");
				scanf("%s", additem_1.newid);
				for (i=0; i <500; i++)
				{
					if (strncmp(additem_1.newid, gstproduct_1.gstcode[i], 5)==0 || strncmp(additem_1.newid, ngstproduct_1.ngstcode[i], 5)==0)
					{
						printf("ID existed! Program exit.");			//Counter to ensure same ID never exist
						goto LOOP;
					}
				}
				printf("Enter item name.\n");
				scanf("%s", additem_1.newname);
				for (i=0; i <5000; i++)
				{
					if (strncmp(additem_1.newname, gstproduct_1.gstname[i], 20)==0 || strncmp(additem_1.newname, ngstproduct_1.ngstname[i], 20)==0)
					{
						printf("Product existed! Program exit.");			// Counter to ensure same PRODUCT never exist
						goto LOOP;
					}
				}
				printf("Enter item price.\n");
				scanf("%f", &additem_1.newprice);
				if (additem_1.newprice == 0)
				{
					printf("Item price can't be 0. Program exit.\n");
					goto LOOP;
				}
				printf("Enter item quantity.\n");
				scanf("%d", &additem_1.newquantity);
				fflush(ngst);
				fprintf(ngst, "\n%.5s;%s;%.2f;%d\n", additem_1.newid, additem_1.newname, additem_1.newprice, additem_1.newquantity);
				fflush(ngst);
			}
			else 
				printf("Error.\n");
			goto LOOP;
			break;
			case'4':
			rewind(gst);
			rewind(ngst);
			rewind(edit);
			while(!feof(edit))
			{
				i=0;
				fscanf(edit, "%5c;%[a-zA-z ];%f;%d\n", productchanges_1.ccode[i], productchanges_1.cname[i], &productchanges_1.cprice[i], &productchanges_1.cquantity[i]);
				i++;
			}
			while (!feof(gst))
			{	
				i=0;		
				fscanf(gst, "%5c;%[a-zA-z ];%f;%d\n", gstproduct_1.gstcode[i], gstproduct_1.gstname[i], &gstproduct_1.gstprice[i], &gstproduct_1.gstquantity[i]);
				i++;
			}
			while(!feof(ngst))
			{
				i=0;
				fscanf(ngst, "%5c;%[a-zA-z ];%f;%d\n", ngstproduct_1.ngstcode[i], ngstproduct_1.ngstname[i], &ngstproduct_1.ngstprice[i], &ngstproduct_1.ngstquantity[i]);
				i++;
			}
			LOOP4:
			printf("This option deletes item.\n");
			printf("Enter id to delete.\n");
			scanf("%s", deleteitem_1.deleteid);
			for (i=0; i< 100; i++)
			{
				if (strncmp(gstproduct_1.gstcode[i], deleteitem_1.deleteid, 5) == 0 && gstproduct_1.gstquantity[i] == 0)
				{
					gstproduct_1.gstcode[i][0] = '\0';
					gstproduct_1.gstname[i][0] = '\0';						//NULLIFY delete variable
					gstproduct_1.gstprice[i] = '\0';
					gstproduct_1.gstquantity[i]='\0';
					remove("gst.txt");
					writegst = fopen("gst.txt", "w+");
					for (x=0; x<100; x++)
					{
						if (gstproduct_1.gstprice[x] != 0)
						{
						fflush(writegst);
						fprintf(writegst, "%.5s;%s;%.2f;%d\n", gstproduct_1.gstcode[x], gstproduct_1.gstname[x], gstproduct_1.gstprice[x], gstproduct_1.gstquantity[x]);
						fflush(writegst);
						x++;
						}
					}
				}
			}
			for (i=0; i< 100; i++)
			{
				if (strncmp(ngstproduct_1.ngstcode[i], deleteitem_1.deleteid, 5) == 0 && gstproduct_1.gstquantity[i] == 0)
				{
					ngstproduct_1.ngstcode[i][0] = '\0';
					ngstproduct_1.ngstname[i][0] = '\0';
					ngstproduct_1.ngstprice[i] = '\0';					//NULLIFY all variable value
					ngstproduct_1.ngstquantity[i]='\0';
					remove("ngst.txt");
					writengst = fopen("ngst.txt", "w+");
					for (x=0; x<100; x++)
					{
						if (ngstproduct_1.ngstprice[x] != 0)
						{
						fflush(writengst);
						fprintf(writengst, "%.5s;%s;%.2f;%d\n", ngstproduct_1.ngstcode[x], ngstproduct_1.ngstname[x], ngstproduct_1.ngstprice[x], ngstproduct_1.ngstquantity[x]);
						fflush(writengst);
						x++;					
						}
					}
				}
			}	
			fclose(writegst);
			printf("Delete process is succesful\n");
			goto LOOP;
			break;
			case '5':
			rewind (gst);
			rewind (ngst);
			printf("---------------------------------------------------------------------------------\n");
			printf("\nGST inventory\n");
			printf("Code\t\tProduct\t\t\tPrice\t\tQuantity\n\n");
			while ( !feof(gst) )
			{
				fscanf(gst, "%5c;%[a-zA-z ];%f;%d\n", gstproduct_1.gstcode[x], gstproduct_1.gstname[x], &gstproduct_1.gstprice[x], &gstproduct_1.gstquantity[x]);
				printf("%-10.5s\t%-20.20s\t%-15.2f\t%d\n", gstproduct_1.gstcode[x], gstproduct_1.gstname[x], gstproduct_1.gstprice[x], gstproduct_1.gstquantity[x]);
				x++;
			}
			printf("--------------------------------------------------------------------------------\n");
			printf("\n\nNGST inventory\n");
			printf("--------------------------------------------------------------------------------\n");
			printf("Code\t\tProduct\t\t\tPrice\t\tQuantity\n\n");
			while ( !feof(ngst) )
			{
				fscanf(ngst, "%5s;%[a-zA-z ];%f;%d\n",  ngstproduct_1.ngstcode[x], ngstproduct_1.ngstname[x], &ngstproduct_1.ngstprice[x], &ngstproduct_1.ngstquantity[x]);	
				printf("%-10.5s\t%-20.20s\t%-15.2f\t%d\n", ngstproduct_1.ngstcode[x], ngstproduct_1.ngstname[x], ngstproduct_1.ngstprice[x], ngstproduct_1.ngstquantity[x]);
				x++;
			}
			printf("--------------------------------------------------------------------------------\n");
			goto LOOP;	
			case'6':
			printf("\nTotal transaction is\t:%d \n", sale);
			if (purchase_1.ramount <= 0)
			{
				printf("Sales with GST is: 0");
			}
			else
			{
				printf("Sales with GST is: %.2f\n", purchase_1.ramount);
			}
			printf("Sales with NGST is\t: %.2f\n", ngsttotal);
			printf("GST collected\t: %.2f\n", totalgst);
			goto LOOP;
			case '7':
			remove("purchase.txt");
			writegst = fopen("purchase.txt", "w+");
			fclose(writegst);
			return 0;
			default :
			printf("Invalid input please try again\n");
			goto LOOP;
		}	
	return 0;
}

void printtable()
{
	printf("------------------------------------\n");
	printf("Grocery Retail\n");
	printf("------------------------------------\n");
	printf("1.\tPurchase items\n");
	printf("2.\tEdit items\n");
	printf("3.\tAdd items\n");
	printf("4.\tDelete items\n");
	printf("5.\tShow inventory\n");
	printf("6.\tShow daily transaction\n");
	printf("7.\tExit\n");
}
