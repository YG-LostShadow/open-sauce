/*
    BlamLib: .NET SDK for the Blam Engine

    Copyright (C) 2005-2010  Kornner Studios (http://kornner.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
namespace BlamLib.Forms
{
	partial class Flags
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
			this.name = new System.Windows.Forms.Label();
			//this.field = new DevComponents.DotNetBar.Controls.ListViewEx();
			this.field = new System.Windows.Forms.ListView();
			this.SuspendLayout();
			// 
			// name
			// 
			this.name.Location = new System.Drawing.Point(16, 4);
			this.name.Name = "name";
			this.name.Size = new System.Drawing.Size(162, 16);
			this.name.TabIndex = 1;
			this.name.Text = "flags";
			this.name.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// field
			// 
			this.field.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)));
			// 
			// 
			// 
			//this.field.Border.Class = "ListViewBorder";
			this.field.CheckBoxes = true;
			this.field.Location = new System.Drawing.Point(184, 0);
			this.field.Name = "field";
			this.field.Size = new System.Drawing.Size(208, 24);
			this.field.TabIndex = 2;
			//this.field.UseCompatibleStateImageBehavior = false;
			this.field.View = System.Windows.Forms.View.List;
			this.field.ItemChecked += new System.Windows.Forms.ItemCheckedEventHandler(this.OnItemChecked);
			// 
			// Flags
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.Controls.Add(this.field);
			this.Controls.Add(this.name);
			this.Name = "Flags";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Label name;
		//private DevComponents.DotNetBar.Controls.ListViewEx field;
		private System.Windows.Forms.ListView field;
	}
}
