package com.sanguo.game.server.connectlogic.common.message.ProtoFriendlyTree
{
	import laya.utils.Byte;
	public class WaterFriendlyTreeReq
	{
		public static const PROTO:String = "ProtoFriendlyTree.WaterFriendlyTreeReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public function WaterFriendlyTreeReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):WaterFriendlyTreeReq
		{
			othuid = undefined;
			this.othuid = msgObj.othuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):WaterFriendlyTreeReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}