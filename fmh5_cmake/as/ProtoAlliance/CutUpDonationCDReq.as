package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class CutUpDonationCDReq
	{
		public static const PROTO:String = "ProtoAlliance.CutUpDonationCDReq";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public function CutUpDonationCDReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.type!= undefined)
			{
				serializeObj.type = this.type;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CutUpDonationCDReq
		{
			type = undefined;
			if(msgObj.hasOwnProperty("type"))
			{
				this.type = msgObj.type;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CutUpDonationCDReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}