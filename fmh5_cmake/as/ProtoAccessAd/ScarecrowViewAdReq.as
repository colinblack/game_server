package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class ScarecrowViewAdReq
	{
		public static const PROTO:String = "ProtoAccessAd.ScarecrowViewAdReq";
		public var package_root:*;
		public  var message:*;
		public var isCostDimaond:int;
		public function ScarecrowViewAdReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			isCostDimaond = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.isCostDimaond!= undefined)
			{
				serializeObj.isCostDimaond = this.isCostDimaond;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ScarecrowViewAdReq
		{
			isCostDimaond = undefined;
			if(msgObj.hasOwnProperty("isCostDimaond"))
			{
				this.isCostDimaond = msgObj.isCostDimaond;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ScarecrowViewAdReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}