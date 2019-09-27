package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class RewardNewShareReq
	{
		public static const PROTO:String = "ProtoActivity.RewardNewShareReq";
		public var package_root:*;
		public  var message:*;
		public var index:int;
		public function RewardNewShareReq(root:*)
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
		public function unserialize(msgObj:*):RewardNewShareReq
		{
			index = undefined;
			this.index = msgObj.index;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardNewShareReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}