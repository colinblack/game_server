package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceWatchAd
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceWatchAd";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public var commons:CommonItemsCPP;
		public var point:int;
		public function ReplyAllianceRaceWatchAd(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
			commons = undefined;
			point = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ret = this.ret;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			if(this.point!= undefined)
			{
				serializeObj.point = this.point;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceWatchAd
		{
			ret = undefined;
			commons = undefined;
			point = undefined;
			this.ret = msgObj.ret;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			if(msgObj.hasOwnProperty("point"))
			{
				this.point = msgObj.point;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceWatchAd
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}