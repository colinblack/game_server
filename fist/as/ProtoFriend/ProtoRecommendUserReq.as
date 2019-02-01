package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoRecommendUserReq
	{
		public static const PROTO:String = "ProtoFriend.ProtoRecommendUserReq";
		public var package_root:*;
		public  var message:*;
		public function ProtoRecommendUserReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoRecommendUserReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoRecommendUserReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}