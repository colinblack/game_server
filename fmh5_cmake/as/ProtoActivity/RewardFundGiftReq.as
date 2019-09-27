package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class RewardFundGiftReq
	{
		public static const PROTO:String = "ProtoActivity.RewardFundGiftReq";
		public var package_root:*;
		public  var message:*;
		public var index:int;
		public function RewardFundGiftReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			index = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.index = this.index;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardFundGiftReq
		{
			index = undefined;
			this.index = msgObj.index;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardFundGiftReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}