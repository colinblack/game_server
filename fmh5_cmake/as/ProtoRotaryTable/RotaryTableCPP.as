package com.sanguo.game.server.connectlogic.common.message.ProtoRotaryTable
{
	import laya.utils.Byte;
	public class RotaryTableCPP
	{
		public static const PROTO:String = "ProtoRotaryTable.RotaryTableCPP";
		public var package_root:*;
		public  var message:*;
		public var gridid:int;
		public var griditemtype:int;
		public var griditemid:int;
		public var griditemcnt:int;
		public function RotaryTableCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			gridid = undefined;
			griditemtype = undefined;
			griditemid = undefined;
			griditemcnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.gridid = this.gridid;
			serializeObj.griditemtype = this.griditemtype;
			if(this.griditemid!= undefined)
			{
				serializeObj.griditemid = this.griditemid;
			}
			serializeObj.griditemcnt = this.griditemcnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RotaryTableCPP
		{
			gridid = undefined;
			griditemtype = undefined;
			griditemid = undefined;
			griditemcnt = undefined;
			this.gridid = msgObj.gridid;
			this.griditemtype = msgObj.griditemtype;
			if(msgObj.hasOwnProperty("griditemid"))
			{
				this.griditemid = msgObj.griditemid;
			}
			this.griditemcnt = msgObj.griditemcnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RotaryTableCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}