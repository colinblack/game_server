package com.sanguo.game.server.connectlogic.common.message.ProtoChampionship
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoJoinInMatchReq
	{
		public static const PROTO:String = "ProtoChampionship.ProtoJoinInMatchReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var heroid:int;
		public var free:int;
		public function ProtoJoinInMatchReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			heroid = undefined;
			free = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.heroid = this.heroid;
			serializeObj.free = this.free;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoJoinInMatchReq
		{
			id = undefined;
			heroid = undefined;
			free = undefined;
			this.id = msgObj.id;
			this.heroid = msgObj.heroid;
			this.free = msgObj.free;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoJoinInMatchReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}