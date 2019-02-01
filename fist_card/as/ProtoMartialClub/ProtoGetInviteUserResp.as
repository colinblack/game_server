package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetInviteUserResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetInviteUserResp";
		public var package_root:*;
		public  var message:*;
		public var users:Vector.<MartialClubUserInfo>;
		public function ProtoGetInviteUserResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			users = new Vector.<MartialClubUserInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.users = [];
			for(var i:int = 0;i < this.users.length;i++)
			{
				serializeObj.users.push(this.users[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetInviteUserResp
		{
			users = new Vector.<MartialClubUserInfo>();
			for(var i:int = 0;i < msgObj.users.length;i++)
			{
				this.users.push(new MartialClubUserInfo(package_root).unserialize(msgObj.users[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetInviteUserResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}