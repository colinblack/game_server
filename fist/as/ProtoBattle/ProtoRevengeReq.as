package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoRevengeReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoRevengeReq";
		public var package_root:*;
		public  var message:*;
		public var enemyId:int;
		public var common:BattleCommon;
		public function ProtoRevengeReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			enemyId = undefined;
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.enemyId = this.enemyId;
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoRevengeReq
		{
			enemyId = undefined;
			common = undefined;
			this.enemyId = msgObj.enemyId;
			this.common = new BattleCommon(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoRevengeReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}