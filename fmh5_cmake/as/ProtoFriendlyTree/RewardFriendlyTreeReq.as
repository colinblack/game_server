package com.sanguo.game.server.connectlogic.common.message.ProtoFriendlyTree
{
	import laya.utils.Byte;
	public class RewardFriendlyTreeReq
	{
		public static const PROTO:String = "ProtoFriendlyTree.RewardFriendlyTreeReq";
		public var package_root:*;
		public  var message:*;
		public function RewardFriendlyTreeReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardFriendlyTreeReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardFriendlyTreeReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}