package com.sanguo.game.server.connectlogic.common.message.ProtoFriendlyTree
{
	import laya.utils.Byte;
	public class GetFriendlyTreeReq
	{
		public static const PROTO:String = "ProtoFriendlyTree.GetFriendlyTreeReq";
		public var package_root:*;
		public  var message:*;
		public function GetFriendlyTreeReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFriendlyTreeReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFriendlyTreeReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}