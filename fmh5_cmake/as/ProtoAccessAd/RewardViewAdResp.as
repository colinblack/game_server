package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class RewardViewAdResp
	{
		public static const PROTO:String = "ProtoAccessAd.RewardViewAdResp";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var commons:CommonItemsCPP;
		public function RewardViewAdResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardViewAdResp
		{
			ts = undefined;
			commons = undefined;
			this.ts = msgObj.ts;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardViewAdResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}