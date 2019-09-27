package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceWatchAd
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceWatchAd";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public function RequestAllianceRaceWatchAd(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceWatchAd
		{
			type = undefined;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceWatchAd
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}