package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperWatchAds
	{
		public static const PROTO:String = "ProtoKeeper.KeeperWatchAds";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var isCostDimaond:int;
		public function KeeperWatchAds(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			isCostDimaond = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			if(this.isCostDimaond!= undefined)
			{
				serializeObj.isCostDimaond = this.isCostDimaond;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):KeeperWatchAds
		{
			id = undefined;
			isCostDimaond = undefined;
			this.id = msgObj.id;
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
		public function decode(buffer:*):KeeperWatchAds
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}