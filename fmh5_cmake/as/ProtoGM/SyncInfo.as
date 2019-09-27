package com.sanguo.game.server.connectlogic.common.message.ProtoGM
{
	import laya.utils.Byte;
	public class SyncInfo
	{
		public static const PROTO:String = "ProtoGM.SyncInfo";
		public var package_root:*;
		public  var message:*;
		public var common:CommonItemsCPP;
		public function SyncInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.common!= undefined)
			{
				serializeObj.common = this.common.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SyncInfo
		{
			common = undefined;
			if(msgObj.hasOwnProperty("common"))
			{
				this.common = new CommonItemsCPP(package_root).unserialize(msgObj.common);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SyncInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}