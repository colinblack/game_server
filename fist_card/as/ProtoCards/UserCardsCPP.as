package com.sanguo.game.server.connectlogic.common.message.ProtoCards
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UserCardsCPP
	{
		public static const PROTO:String = "ProtoCards.UserCardsCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var cardId:int;
		public var star:int;
		public function UserCardsCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			ud = undefined;
			cardId = undefined;
			star = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.cardId = this.cardId;
			if(this.star!= undefined)
			{
				serializeObj.star = this.star;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):UserCardsCPP
		{
			ud = undefined;
			cardId = undefined;
			star = undefined;
			this.ud = msgObj.ud;
			this.cardId = msgObj.cardId;
			if(msgObj.hasOwnProperty("star"))
			{
				this.star = msgObj.star;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UserCardsCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}