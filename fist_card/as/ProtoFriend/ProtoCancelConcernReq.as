package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCancelConcernReq
	{
		public static const PROTO:String = "ProtoFriend.ProtoCancelConcernReq";
		public var package_root:*;
		public  var message:*;
		public var otherId:int;
		public function ProtoCancelConcernReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			otherId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.otherId = this.otherId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCancelConcernReq
		{
			otherId = undefined;
			this.otherId = msgObj.otherId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCancelConcernReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}