
namespace PruebaControl
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            portOptionsBox = new ComboBox();
            portsLabel = new Label();
            portConnectBtn = new Button();
            label1 = new Label();
            label2 = new Label();
            leftStatus = new Label();
            rightStatus = new Label();
            SuspendLayout();
            // 
            // portOptionsBox
            // 
            portOptionsBox.FormattingEnabled = true;
            portOptionsBox.Location = new Point(12, 31);
            portOptionsBox.Name = "portOptionsBox";
            portOptionsBox.Size = new Size(121, 23);
            portOptionsBox.TabIndex = 0;
            // 
            // portsLabel
            // 
            portsLabel.AutoSize = true;
            portsLabel.Location = new Point(12, 13);
            portsLabel.Name = "portsLabel";
            portsLabel.Size = new Size(53, 15);
            portsLabel.TabIndex = 1;
            portsLabel.Text = "Puertos: ";
            // 
            // portConnectBtn
            // 
            portConnectBtn.Location = new Point(139, 30);
            portConnectBtn.Name = "portConnectBtn";
            portConnectBtn.Size = new Size(75, 23);
            portConnectBtn.TabIndex = 2;
            portConnectBtn.Text = "CONECTAR";
            portConnectBtn.UseVisualStyleBackColor = true;
            portConnectBtn.Click += portConnectBtn_Click_1;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(27, 105);
            label1.Name = "label1";
            label1.Size = new Size(68, 15);
            label1.TabIndex = 3;
            label1.Text = "R. Izquierda";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(139, 105);
            label2.Name = "label2";
            label2.Size = new Size(63, 15);
            label2.TabIndex = 4;
            label2.Text = "R. Derecha";
            // 
            // leftStatus
            // 
            leftStatus.AutoSize = true;
            leftStatus.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            leftStatus.Location = new Point(44, 136);
            leftStatus.Name = "leftStatus";
            leftStatus.Size = new Size(21, 21);
            leftStatus.TabIndex = 5;
            leftStatus.Text = "~";
            leftStatus.TextAlign = ContentAlignment.TopCenter;
            // 
            // rightStatus
            // 
            rightStatus.AutoSize = true;
            rightStatus.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            rightStatus.Location = new Point(158, 136);
            rightStatus.Name = "rightStatus";
            rightStatus.Size = new Size(21, 21);
            rightStatus.TabIndex = 6;
            rightStatus.Text = "~";
            rightStatus.TextAlign = ContentAlignment.TopCenter;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(409, 303);
            Controls.Add(rightStatus);
            Controls.Add(leftStatus);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(portConnectBtn);
            Controls.Add(portsLabel);
            Controls.Add(portOptionsBox);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        private void buttonALabel_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        #endregion

        private ComboBox portOptionsBox;
        private Label portsLabel;
        private Button portConnectBtn;
        private Label label1;
        private Label label2;
        private Label leftStatus;
        private Label rightStatus;
    }
}
