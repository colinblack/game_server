package com.sanguo.game.server.connectlogic.common.message.ProtoRotaryTable
{
	import laya.utils.Byte;
	public class GetRotaryTableInfoResp
	{
		public static const PROTO:String = "ProtoRotaryTable.GetRotaryTableInfoResp";
		public var package_root:*;
		public  var message:*;
		public var rotarytable:Vector.<RotaryTableCPP>;
		public var drawinfo:DrawCntCPP;
		public function GetRotaryTableInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			rotarytable = new Vector.<RotaryTableCPP>();
			drawinfo = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.rotarytable = [];
			for(var i:int = 0;i < this.rotarytable.length;i++)
			{
				serializeObj.rotarytable.push(this.rotarytable[i].serialize());
			}
			serializeObj.drawinfo = this.drawinfo.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetRotaryTableInfoResp
		{
			rotarytable = new Vector.<RotaryTableCPP>();
			drawinfo = undefined;
			for(var i:int = 0;i < msgObj.rotarytable.length;i++)
			{
				this.rotarytable.push(new RotaryTableCPP(package_root).unserialize(msgObj.rotarytable[i]));
			}
			this.drawinfo = new DrawCntCPP(package_root).unserialize(msgObj.drawinfo);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetRotaryTableInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}