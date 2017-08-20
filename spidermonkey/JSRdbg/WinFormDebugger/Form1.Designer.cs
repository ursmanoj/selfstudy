namespace WindowsFormsApp1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtBoxResponse = new System.Windows.Forms.TextBox();
            this.srcCodeList = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // txtBoxResponse
            // 
            this.txtBoxResponse.Location = new System.Drawing.Point(744, 24);
            this.txtBoxResponse.Multiline = true;
            this.txtBoxResponse.Name = "txtBoxResponse";
            this.txtBoxResponse.ReadOnly = true;
            this.txtBoxResponse.Size = new System.Drawing.Size(705, 834);
            this.txtBoxResponse.TabIndex = 0;
            // 
            // srcCodeList
            // 
            this.srcCodeList.FormattingEnabled = true;
            this.srcCodeList.ItemHeight = 16;
            this.srcCodeList.Items.AddRange(new object[] {
            "debugger;",
            "print(\'Manoj. \');",
            "var a = \"Unchanged\";",
            "//var func = function () {",
            "\tprint(\"Changing value of a to changed\");",
            "\ta = \"changed\";",
            "//}",
            "//func();",
            "print(\"New value of a:\" + a);"});
            this.srcCodeList.Location = new System.Drawing.Point(141, 24);
            this.srcCodeList.Name = "srcCodeList";
            this.srcCodeList.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.srcCodeList.Size = new System.Drawing.Size(529, 596);
            this.srcCodeList.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1471, 870);
            this.Controls.Add(this.srcCodeList);
            this.Controls.Add(this.txtBoxResponse);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtBoxResponse;
        private System.Windows.Forms.ListBox srcCodeList;
    }
}

