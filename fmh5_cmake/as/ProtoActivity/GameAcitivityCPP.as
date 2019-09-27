package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GameAcitivityCPP
	{
		public static const PROTO:String = "ProtoActivity.GameAcitivityCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var version:int;
		public var actdata:Vector.<int>;
		public function GameAcitivityCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			version = undefined;
			actdata = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.version = this.version;
			serializeObj.actdata = [];
			for(var i:int = 0;i < this.actdata.length;i++)
			{
				serializeObj.actdata.push(this.actdata[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GameAcitivityCPP
		{
			id = undefined;
			version = undefined;
			actdata = new Vector.<int>();
			this.id = msgObj.id;
			this.version = msgObj.version;
			for(var i:int = 0;i < msgObj.actdata.length;i++)
			{
				this.actdata.push(msgObj.actdata[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GameAcitivityCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}