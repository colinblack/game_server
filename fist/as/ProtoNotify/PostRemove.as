package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class PostRemove
	{
		public static const PROTO:String = "ProtoNotify.PostRemove";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public var id:int;
		public function PostRemove(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			type = undefined;
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PostRemove
		{
			type = undefined;
			id = undefined;
			this.type = msgObj.type;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PostRemove
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}