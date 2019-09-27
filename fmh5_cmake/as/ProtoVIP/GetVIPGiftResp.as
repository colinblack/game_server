package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class GetVIPGiftResp
	{
		public static const PROTO:String = "ProtoVIP.GetVIPGiftResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var rewardts:int;
		public function GetVIPGiftResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			rewardts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.rewardts = this.rewardts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetVIPGiftResp
		{
			commons = undefined;
			rewardts = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.rewardts = msgObj.rewardts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetVIPGiftResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}